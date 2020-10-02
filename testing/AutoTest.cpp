#include <unordered_map>
#include "gtest/gtest.h"

bool contains(std::string word, std::string substring) {
    auto index = word.find(substring);
    return (index != std::string::npos);
}

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

TEST(AutoTest, enums) {
    enum Color {Red, Blue, Green};
    EXPECT_EQ(1, Blue); // works but gross

    enum class Flavor {Chocolate, Vanilla, Twist};
    Flavor favorite = Flavor::Chocolate;
    EXPECT_EQ(Flavor::Chocolate, favorite);

    struct Cone {
        enum class Base { Chocolate, Vanilla, Twist, Strawberry };
        enum class Topping { Sprinkles, Jimmies, Dip };

        Base base;
        Topping topping;

        Cone(Base base, Topping topping): base(base), topping(topping) {}
    };

    Cone mine { Cone::Base::Chocolate, Cone::Topping::Jimmies };
    auto topping = mine.topping;
    EXPECT_EQ(Cone::Topping::Jimmies, topping);
    EXPECT_TRUE(contains(typeid(topping).name(), "Cone"));
    EXPECT_TRUE(contains(typeid(topping).name(), "Topping"));
    EXPECT_FALSE(contains(typeid(topping).name(), "Jimmies"));
}

TEST(AutoTest, forloops) {
    std::vector<int> numbers{1, 2, 3, 4};
    for (auto& number : numbers) {
        number = 1;
    }

    EXPECT_EQ(1, numbers.at(3));

    std::vector<bool> beliefs{false, false, false, false};

    // because we are assigning to an rvalue we need auto&& or const auto& instead of auto&
    for (const auto& belief : beliefs) {
        // look but don't change
    }


    for (auto&& belief : beliefs) {
        belief = true;
    }
    EXPECT_TRUE(beliefs.at(3));
}
