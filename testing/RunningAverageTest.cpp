#include "gtest/gtest.h"
#include "RunningAverage.h"
TEST(RunningAverageTests, BadButEasy) {
    auto ra = new BadRunningAverage();
    ra->push(1);
    int one = ra->push(1);

    EXPECT_EQ(one, 1);
}

TEST(RunningAverageTests, Bad) {
    auto ra = new BadRunningAverage();
    ra->push(0);
    ra->push(0);

    for (int ctr=0; ctr<100;ctr++) {
        ra->push(1);
    }
    int still_zero = ra->push(1);

    EXPECT_EQ(still_zero, 0);
}

TEST(RunningAverageTests, Good) {
    auto ra = new GoodRunningAverage();
    ra->push(0);
    ra->push(0);

    for (int ctr=0; ctr<100;ctr++) {
        ra->push(1);
    }
    int one = ra->push(1);

    EXPECT_EQ(one, 1);
}
