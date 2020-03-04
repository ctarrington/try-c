#include "gtest/gtest.h"

TEST(SimpleCollectionsTest, usage) {
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
}
