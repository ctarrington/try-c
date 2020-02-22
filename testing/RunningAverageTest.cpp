#include "gtest/gtest.h"
#include "BadRunningAverage.h"
#include "GoodRunningAverage.h"


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

TEST(RunningAverageTests, GoodInts) {
    GoodRunningAverage<int> *ra = new GoodRunningAverage<int>();
    ra->push(0);
    ra->push(0);

    for (int ctr=0; ctr<100;ctr++) {
        ra->push(1);
    }
    int one = ra->push(1);

    EXPECT_EQ(one, 1);
}

TEST(RunningAverageTests, GoodLongs) {
    GoodRunningAverage<long> *ra = new GoodRunningAverage<long>();
    ra->push(0L);
    ra->push(0L);

    for (int ctr=0; ctr<100;ctr++) {
        ra->push(1L);
    }
    int one = ra->push(1L);

    EXPECT_EQ(one, 1);
}


TEST(RunningAverageTests, ImpossibleToAverageStrings) {
    // Won't compile
    // GoodRunningAverage<std::string> *impossibleRa = new GoodRunningAverage<std::string>();
}

TEST(RunningAverageTests, NoCopies) {
    GoodRunningAverage<int> *ra = new GoodRunningAverage<int>();
    GoodRunningAverage<int> *rb = new GoodRunningAverage<int>();

    // Won't compile - call to deleted constructor
    // GoodRunningAverage<int> other = *ra;

    // Won't compile - deleted operator
    // *rb = *ra;
}

template<typename T>
void push_one_to_average(GoodRunningAverage<T> &ra) {
    ra.push(1);
}


TEST(RunningAverageTests, Passable) {
    GoodRunningAverage<int> *ra = new GoodRunningAverage<int>();
    push_one_to_average(*ra);
    EXPECT_EQ(ra->push(5), 3);

}

