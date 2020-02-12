#include "gtest/gtest.h"
#include "Greeting.h"


TEST(SillyTests, Big) {
    EXPECT_GT(3, 1);
}

TEST(SillyTests, Greet) {
    auto greeting = new Greeting("Hi");
    EXPECT_EQ(greeting->sayHelloTo("Joe"), "Hi, Joe");
}
