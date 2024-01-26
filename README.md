# PS6: RandWriter

## Contact
Name: Patricia Antlitz
Section: 202
Time to Complete: ~ 7 hrs


## Description
The RandWriter project is designed to implement a MArkov model for generating pseudo-random text. Leveraging the principles outlined by Claude Shannon in his landmark paper, the program analyzes input text for transitions between k-grams, constructs a probabilistic model of the text, and utilizes this model to generate text that exhibits reasonable patterns. The underlying Markov model captures the statistical structure of the input text, providing a foundation for context-aware text generation.

### Features
The major decisions in the project include:
- Order of the MArkov Model: The program allows users to specify the order(k) of the Markov model, influencing the level of context considered during text generation.
- Data structure Choice: The implementation uses a symbol table with nested structures to efficiently store and retrieve frequency counts for k-grams and their subsequent characters.
- Test Generation Strategy: The program employs a dynamic approach to simulate a trajectory through the  Markov chain, ensuring that generated text reflects the statistical properties of the inout text.

One interesting aspect of the project implementation is the utilization of a circular text representation to address transitions between the end and beginning of the input text. By considering the text as circular, the Markov model accurately captures the statistical properties even at the boundary, ensuring a seamless and contextually relevant text generation.

Another feature is the dynamic ordering of characters in the internal state display. A lambda function was employed to customize the sorting criteria when presenting the Markov model's alphabet. This allows for a more insightful representation, showcasing characters in descending order of their frequencies in the input text.

### Testing
- Unit tests: Unit tests were written for each method in the RandWriter class to ensure correct functionality
- Markov Model Accuracy = Tests were conducted to verify that Markov model accurately represents the input text and its transitions between k-grams.
- Generated Text Validation: The generated text was validated against expected patterns and statistical characteristics.

### Lambda
A lambda expression was used in the implementation to sort the characters based on their frequencies when displaying the internal state of the Markov model. The lambda function was passed to the `std::sort` algorithm to customized the sorting criterial:
```c++
// example lambda
std::sort(alphabet.begin(), alphabet.end(), [&freqMap](char a, char b) {
    return freqMao[a] > freqMap[b];
})
```
I originally added the lambda function as a parameter to the method kRand. However, the autograder didnt like it. Since to me, that was the best method for a parameter implementation, I decided to add the lambda function inside of the method instead,

### Issues
Challenges faced during the project:
- Circular Text Consideration = ensuring taht the Markov model appropriately handles circular text (repeating the first k characters at the end) required careful implementation.
- Efficiency Concerns = Balancing efficiency with accuracy in the Markov model contruction, especially for large input texts, took me extra time.

### Extra Credit
Anything special you did.  This is required to earn bonus points.

## Acknowledgements
c++ documentation and class materials
