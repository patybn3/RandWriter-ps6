/*
    Copyright 2023 Patricia Antlitz
*/
#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <functional>
#include <random>

class RandWriter {
 public:
    RandWriter(std::string text, size_t k);

    int orderK() const;
    int freq(std::string kGram) const;
    int freq(std::string kGram, char c) const;

    char kRand(std::string kGram);

    std::string generate(std::string kGram, size_t L);

    friend std::ostream& operator<<(std::ostream& os, const RandWriter& rw);

 private:
    size_t k;
    std::unordered_map<std::string, std::unordered_map<char, int>> markovModel;
    std::map<std::string, int> kGramFreq;
    std::string alphabet;

    void validateKGramLength(const std::string& kGram) const;
};
