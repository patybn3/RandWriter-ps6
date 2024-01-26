/*
    Copyright 2023 Patricia Antlitz
*/
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/included/unit_test.hpp>
#include "RandWriter.hpp"

BOOST_AUTO_TEST_CASE(constructorTest) {
    BOOST_REQUIRE_NO_THROW(RandWriter("gagggagaggcgagaaa", 2));
    BOOST_REQUIRE_THROW(RandWriter("ga", 3), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(orderKTest) {
    RandWriter rand("gagggagaggcgagaaa", 2);
    BOOST_REQUIRE_EQUAL(rand.orderK(), 2);
}

BOOST_AUTO_TEST_CASE(freqTest) {
    RandWriter rand("gagggagaggcgagaaa", 2);
    // frequency of kGram
    BOOST_REQUIRE_EQUAL(rand.freq("ga"), 5);
    BOOST_REQUIRE_EQUAL(rand.freq("gg"), 3);

    // frequency of kGram followed by a character
    BOOST_REQUIRE_EQUAL(rand.freq("ga", 'g'), 4);
    BOOST_REQUIRE_EQUAL(rand.freq("gg", 'g'), 1);
    BOOST_REQUIRE_EQUAL(rand.freq("gg", 'a'), 1);

    // non-existent kGram:
    BOOST_REQUIRE_EQUAL(rand.freq("zz", '1'), 0);
}

BOOST_AUTO_TEST_CASE(kRandTest) {
    RandWriter rand("gagggagaggcgagaaa", 2);

    // test for valid kGram:
    BOOST_REQUIRE_NO_THROW(rand.kRand("ga"));
    // test kRand for a non-existent kGram
    BOOST_REQUIRE_THROW(rand.kRand("zz"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(generateTest) {
    RandWriter rand("gagggagaggcgagaaa", 2);
    // test generate with valid input
    BOOST_REQUIRE_NO_THROW(rand.generate("ga", 10));
    // test with invalid kGram
    BOOST_REQUIRE_THROW(rand.generate("zz", 10), std::invalid_argument);
    // generate with L less than k
    BOOST_REQUIRE_THROW(rand.generate("ga", 1), std::invalid_argument);
}
