#include <unordered_map>
#include "gtest/gtest.h"

class Holder {
    int value;

public:
    Holder(int const _value): value{_value} {}

    int& get_modifiable_value() {
        return value;
    }

};

TEST(AutoTest, references) {
    auto x = 1;
    EXPECT_STREQ("i", typeid(x).name());

    std::vector<int> v {1,2,3,4};
    auto first = v[0];
    auto last = v[v.size()-1];
    EXPECT_EQ(1, v.at(0));
    EXPECT_EQ(1, first);
    EXPECT_EQ(4, last);

    auto& first_ref = v[0];
    first_ref = 11;
    EXPECT_EQ(11, v.at(0));

    Holder holder(11);

    auto& y = holder.get_modifiable_value();
    y = 33;
    EXPECT_EQ(33, holder.get_modifiable_value());

    auto z = holder.get_modifiable_value();
    z = 66;
    EXPECT_EQ(33, holder.get_modifiable_value()); // still 33 because z is an int not an int&
}

TEST(AutoTest, containers) {
    std::unordered_map<std::string, int> lookup {{"hi", 1}, {"there", 2}};

    auto value = lookup.at("hi");
    EXPECT_EQ(1, value);

    std::unordered_map<int, std::string> reverse {};
    for (auto name_value_pair : lookup) {
        reverse[name_value_pair.second] = name_value_pair.first;
    }

    EXPECT_EQ("hi", reverse[1]);
}
