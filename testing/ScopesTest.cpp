#include "gtest/gtest.h"

static int accessCounter = 0;

int collect(int value) {
    static int accumulated = 0;

    accumulated += value;
    accessCounter++;
    return accumulated;
}

TEST(ScopesTest, static) {
    int c = collect(10);
    EXPECT_EQ(10, c);

    c = 1000;
    EXPECT_EQ(1000, c);

    c = collect(10);
    EXPECT_EQ(20, c);

    EXPECT_EQ(2, accessCounter);
}