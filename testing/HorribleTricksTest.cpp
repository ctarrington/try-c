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

TEST(HorribleTricksTests, iterationFromPointer) {
    string name = "Fred Flint";
    char fname[5] = "";
    char lname[6] = "";
    int fPosition = 0;
    int lPosition = 0;

    for (string::const_iterator charItr = name.cbegin(); charItr != name.cend(); charItr++) {
        int offset = charItr - name.cbegin();

        if (offset < 4) {
            fname[fPosition++] = *charItr;
        } else if (offset > 4 && offset < 10) {
            lname[lPosition++] = *charItr;
        }
    }

    EXPECT_STREQ("Fred", fname);
    EXPECT_STREQ("Flint", lname);
}

TEST(HorribleTricksTests, alternativeIteration) {
    string name = "Fred Flint";
    char fname[5] = "";
    char lname[6] = "";
    int fPosition = 0;
    int lPosition = 0;

    int index = 0;
    for (string::const_iterator charItr = name.cbegin(); charItr != name.cend(); charItr++, index++) {
        if (index < 4) {
            fname[fPosition++] = *charItr;
        } else if (index > 4 && index < 10) {
            lname[lPosition++] = *charItr;
        }
    }

    EXPECT_STREQ("Fred", fname);
    EXPECT_STREQ("Flint", lname);
}