/*
    Copyright 2023 Patricia Antlitz
*/
#include <ctime>
#include "RandWriter.hpp"

RandWriter::RandWriter(std::string text, size_t k) : k(k) {
    if (text.length() < k) {
        throw std::invalid_argument("Text length is less than order");
    }

    // circular text to simulate repeating the first k characters at the end
    text += text.substr(0, k);

    // building Markov Model
    for (size_t i = 0; i < text.length() - k; ++i) {
        std::string currentKGram = text.substr(i, k);
        char nextChar = text[i + k];

        // Update Markov
        markovModel[currentKGram][nextChar]++;
        kGramFreq[currentKGram]++;
    }

    for (char c : text) {
        if (alphabet.find(c) == std::string::npos) {
            alphabet += c;
        }
    }
}

int RandWriter::orderK() const {
    return k;
}

// number of occurrences of kgram in text
int RandWriter::freq(std::string kGram) const {
    validateKGramLength(kGram);

    if (kGramFreq.find(kGram) != kGramFreq.end()) {
        return kGramFreq.at(kGram);
    } else {
        return 0;
    }
}

// number of times that character c follows kGram
int RandWriter::freq(std::string kGram, char c) const {
    validateKGramLength(kGram);

    if (markovModel.find(kGram) != markovModel.end() &&
        markovModel.at(kGram).find(c)!= markovModel.at(kGram).end()) {
        return markovModel.at(kGram).at(c);
    } else {
        return 0;
    }
}

// Random character following given kGram
char RandWriter::kRand(std::string kGram) {
    validateKGramLength(kGram);

    if (markovModel.find(kGram) == markovModel.end()) {
        throw std::invalid_argument("No such k-gram in the Markov Model");
    }

    const std::unordered_map<char, int>& charFreq = markovModel.at(kGram);

    // generate a random index based on the frequencies
    int totalFreq = 0;
    for (const auto& entry : charFreq) {
        totalFreq += entry.second;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, totalFreq - 1);
    unsigned int randomValue = dis(gen);

    // lambda function to get a random character based on frequencies
    auto getRandomChar = [&]() {
        // find the corresponding character based on the random index
        unsigned int cumulativeFreq = 0;
        for (const auto& entry : charFreq) {
            cumulativeFreq += entry.second;
            if (randomValue < cumulativeFreq) {
                return entry.first;
            }
        }
        throw std::runtime_error("Error in generating a random character");
    };
    return getRandomChar();
}

// Generate a string of length L characters
std::string RandWriter::generate(std::string kGram, size_t L) {
    validateKGramLength(kGram);

    if (kGram.length() != k || L < k) {
        throw std::invalid_argument("Length should be at least equal to order k");
    }

    std::string generatedText = kGram;

    for (size_t i = 0; i < L - k; ++i) {
        char nextChar = kRand(kGram);
        generatedText += nextChar;
        kGram = kGram.substr(1) + nextChar;
    }

    return generatedText;
}

std::ostream& operator<<(std::ostream& os, const RandWriter& rw) {
    os << "Order: " << rw.k << "\nAlphabet: " << rw.alphabet <<
            "\n\nK-grams Frequencies:" << std::endl;

    for (const auto& entry : rw.kGramFreq) {
        os << entry.first << ": " << entry.second << std::endl;
    }

    os << "\nMarkov Model:" << std::endl;

    for (const auto& entry : rw.markovModel) {
        os << entry.first << "->";
        for (const auto& charEntry : entry.second) {
            os << charEntry.first << ": " << charEntry.second << ", ";
        }
        os << std::endl;
    }
    return os;
}

void RandWriter::validateKGramLength(const std::string& kGram) const {
    if (kGram.length() != k) {
        throw std::invalid_argument("K-gram length is not equal to order k");
    }
}
