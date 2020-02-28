#include "gtest/gtest.h"

using namespace std;

class Person {

public:
    Person(int weight, double height, float accountBalance) {
        this->weight = weight;
        this->height = height;
        this->accountBalance = accountBalance;
    }

    Person(const Person&) = default;
    Person& operator=(const Person&) = default;

    int weight;
    int height;
    float accountBalance;

};

TEST(HorribleTricksTests, calculateOffset) {
    Person* joe = new Person(100, 60, 2345.67);

    size_t weight_offset = (size_t)&((Person*)0)->weight;
    EXPECT_EQ(0, weight_offset);

    size_t height_offset = (size_t)&((Person*)0)->height;
    EXPECT_EQ(4, height_offset);

    size_t balance_offset = (size_t)&((Person*)0)->accountBalance;
    EXPECT_EQ(8, balance_offset);

    char* buffer = (char*) joe;
    int height = (int) buffer[height_offset];
    EXPECT_EQ(height, joe->height);
}

TEST(HorribleTricksTests, charactersForNumbers) {
    // horrible is a bit of an overstatement.
    char sevenChar = 7;
    char sevenString[6];
    sprintf(sevenString, "%hhd.0", sevenChar);
    EXPECT_STREQ("7.0", sevenString);

    short seven = 7;
    sprintf(sevenString, "%hhd.0", seven);
    EXPECT_STREQ("7.0", sevenString);

    // as a one byte savings isn't nothing
    int savings = sizeof(seven) - sizeof(sevenChar);
    EXPECT_EQ(1, savings);
}