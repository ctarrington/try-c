#include "gtest/gtest.h"
#include <array>

using namespace std;

array<int, 5> numbers{ {1,2,3,4,5} };

TEST(PredicatesTest, functor) {

    struct BelowFunctor {
        int max{0};
        BelowFunctor(const int& _max) : max{_max} {};
        bool operator () (const int& value) {
            return value < max;
        }
    };

    int small = count_if(numbers.cbegin(), numbers.cend(), BelowFunctor(3));
    EXPECT_EQ(2, small);
}

TEST(PredicatesTest, readableClosure) {
    const int max{3};
    auto belowPredicate = [max] (const int& value) { return value < max; };

    int small = count_if(numbers.cbegin(), numbers.cend(), belowPredicate);
    EXPECT_EQ(2, small);
}

TEST(PredicatesTest, inlineClosure) {
    const int max{3};
    int small = count_if(numbers.cbegin(), numbers.cend(), [max] (const int& value) { return value < max; });
    EXPECT_EQ(2, small);
}
