#include "gtest/gtest.h"

using namespace std;

TEST(GreeterFunctionTest, simple) {
    const char* greeting = "Hi";
    auto greet = [greeting](const char* name, char* destinationBuffer) {
        sprintf(destinationBuffer, "%s, %s", greeting, name);
        return destinationBuffer;
    };

    char sentence[50];
    greet("Fred", sentence);
    EXPECT_STREQ("Hi, Fred", greet("Fred", sentence));
}
