#include "gtest/gtest.h"

#include <boost/date_time/gregorian/gregorian.hpp>

TEST(BoostDatesTests, simpleConstruction) {
    boost::gregorian::date d{ 1986, 9, 15 };

    EXPECT_EQ(1986, d.year());
}

