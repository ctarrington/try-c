#include "gtest/gtest.h"

#include <boost/format.hpp>


TEST(GreeterFunctionTest, oldSchool) {
    const char* greeting = "Hi";

    auto greet = [greeting](const char* name, char* destinationBuffer, char endMark = '.') {
        sprintf(destinationBuffer, "%s, %s%c", greeting, name, endMark);
        return destinationBuffer;
    };

    char sentence[50];
    EXPECT_STREQ("Hi, Fred.", greet("Fred", sentence));
    EXPECT_STREQ("Hi, Fred!", greet("Fred", sentence, '!'));
}


TEST(GreeterFunctionTest, newSchool) {
    boost::format format("Hi, %1%%2%");

    std::string greeting = str(format % "Fred" % "!");
    EXPECT_STREQ("Hi, Fred!", greeting.c_str());
}


