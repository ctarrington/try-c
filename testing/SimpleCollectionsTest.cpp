#include <array>
#include <vector>
#include <algorithm>

#include "gtest/gtest.h"

TEST(SimpleCollectionsTest, arrayUsage) {
    std::array<int, 10> numbers {1,2,3};
    EXPECT_EQ(3, numbers[2]);
    EXPECT_EQ(0, numbers.at(3));

    numbers.at(3) = 4;
    EXPECT_EQ(4, numbers.at(3));

    EXPECT_EQ(4, std::get<3>(numbers));

    // compile time issue
    // int nope = std::get<10>(numbers);

    EXPECT_THROW(numbers.at(10), std::out_of_range);
    EXPECT_ANY_THROW(numbers.at(10));

    int* numbersP = numbers.data();
    EXPECT_EQ(1, *numbersP++);
    EXPECT_EQ(2, *numbersP++);

    int sum = 0;
    for (auto itr = numbers.begin();itr != numbers.end();itr++) {
        sum += *itr;
    }
    EXPECT_EQ(10, sum);

    sum = 0;
    for (const int number : numbers) {
        sum += number;
    }
    EXPECT_EQ(10, sum);
}

TEST(SimpleCollectionsTest, vectorUsage) {
    std::vector<int> odds{1};

    odds.insert(odds.end(), 3);
    odds.push_back(5);
    odds.insert(odds.begin(), -1);
    odds.insert(odds.begin() + 4, 7);

    EXPECT_EQ(-1, odds.at(0));
    EXPECT_EQ(5, odds.at(3));
    EXPECT_EQ(7, odds.at(4));
}

TEST(SimpleCollectionsTest, pairsUsage) {
    std::pair<std::string, int> fred{"Fred", 123};
    EXPECT_STREQ("Fred", fred.first.c_str());
    EXPECT_EQ(123, fred.second);

    std::pair<std::string, int> ted{"Ted", 456};
    swap(fred, ted);
    EXPECT_STREQ("Fred", ted.first.c_str());
    EXPECT_EQ(123, ted.second);

    fred.swap(ted);
    EXPECT_STREQ("Ted", ted.first.c_str());
    EXPECT_EQ(456, ted.second);

    std::pair<std::string, int> otherTed{"Ted", 456};
    EXPECT_TRUE(ted == otherTed);
    EXPECT_TRUE(fred != ted);
}

TEST(SimpleCollectionsTest, reverse) {
    std::vector<int> odds{1,3,5,7,9,11};
    std::reverse(odds.begin(), odds.end());
    EXPECT_EQ(11, odds.at(0));
}


