#include <ratio>

#include "gtest/gtest.h"

using std::ratio;
using std::ratio_multiply;
using std::ratio_divide;
using std::ratio_subtract;

TEST(MathTidbitsTests, compileTimeMath) {
    using one_third = ratio<1, 3>;
    using five_halves = ratio<5, 2>;
    using five_sixth = ratio_multiply<one_third, five_halves>;
    using three_sixth = ratio_subtract<five_sixth, ratio<1,3>>;

    EXPECT_EQ(five_sixth::num, 5);
    EXPECT_EQ(five_sixth::den, 6);

    float result = (float) five_sixth::num / (float) five_sixth::den;
    EXPECT_NEAR(result, 0.8333, 0.0001);

    // simplified
    EXPECT_EQ(three_sixth::num, 1);
    EXPECT_EQ(three_sixth::den, 2);
}

TEST(MathTidbitsTests, conversions) {
    auto fortyTwo = std::stoi("42");
    auto seven = std::stoi("111", nullptr, 2);

    EXPECT_EQ(42, fortyTwo);
    EXPECT_EQ(7, seven);

    std::string raw = "123 890";
    size_t next;
    auto oneTwentyThree = std::stoi(raw, &next, 10);
    auto eightNinety = std::stoi(raw.substr(next));
    EXPECT_EQ(123, oneTwentyThree);
    EXPECT_EQ(890, eightNinety);
}