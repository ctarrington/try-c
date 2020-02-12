#include "gtest/gtest.h"
#include "Greeting.h"

TEST(GreetingTests, Greet) {
    auto greeting = new Greeting("Hi");
    EXPECT_EQ(greeting->sayHelloTo("Joe"), "Hi, Joe");
}
