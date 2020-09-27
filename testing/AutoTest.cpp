#include "gtest/gtest.h"

class Holder {
    int value;

public:
    Holder(int const _value): value{_value} {}

    int& get_modifiable_value() {
        return value;
    }

};

TEST(AutoTest, simple) {
    auto x = 1;
    EXPECT_STREQ("i", typeid(x).name());
}

TEST(AutoTest, references) {
    Holder holder(11);

    auto& y = holder.get_modifiable_value();
    y = 33;
    EXPECT_EQ(33, holder.get_modifiable_value());

    auto z = holder.get_modifiable_value();
    z = 66;
    EXPECT_EQ(33, holder.get_modifiable_value()); // still 33 because z is an int not an int&
}