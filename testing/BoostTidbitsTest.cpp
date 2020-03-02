#include <iostream>

#include "gtest/gtest.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/filesystem.hpp>
using namespace boost::filesystem;

TEST(BoostTidbitsTests, simpleDateConstruction) {
    boost::gregorian::date d{ 1986, 9, 15 };

    EXPECT_EQ(1986, d.year());
}


TEST(BoostTidbitsTests, currentPath) {
    path path = current_path();
    std::string cwd = path.string();
    int index = cwd.find("test");
    EXPECT_GT(index, 0);
}