#include "gtest/gtest.h"

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
    int height = static_cast<int>(buffer[height_offset]);
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
    std::string name = "Fred Flint";
    char fname[5] = "";
    char lname[6] = "";
    int fPosition = 0;
    int lPosition = 0;

    auto name_cend = name.cend();
    for (std::string::const_iterator charItr = name.cbegin(); charItr != name_cend; charItr++) {
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
    std::string name = "Fred Flint";
    char fname[5] = "";
    char lname[6] = "";
    int fPosition = 0;
    int lPosition = 0;

    int index = 0;
    auto name_cend = name.cend();
    for (std::string::const_iterator charItr = name.cbegin(); charItr != name_cend; charItr++, index++) {
        if (index < 4) {
            fname[fPosition++] = *charItr;
        } else if (index > 4 && index < 10) {
            lname[lPosition++] = *charItr;
        }
    }

    EXPECT_STREQ("Fred", fname);
    EXPECT_STREQ("Flint", lname);
}

TEST(HorribleTricksTests, constCast) {
    const int& safe_int = 4;
    // safe_int = 5; //nope

    int& unsafe_int = const_cast<int&>(safe_int);
    EXPECT_EQ(4,unsafe_int);

    unsafe_int = 6;
    EXPECT_EQ(6, unsafe_int);
    EXPECT_EQ(6, safe_int);
}
