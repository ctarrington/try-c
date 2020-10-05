#include "gtest/gtest.h"

class IIThing {

public:
    static int numConstructions;
    static int numCopies;

    static void resetCounts() {
        numCopies = 0;
        numConstructions = 0;
    }

    std::string name;

    IIThing(std::string _name) :
        name{_name} {
        numConstructions++;
    };

    IIThing(const IIThing& other) : name{other.name} {
        numCopies++;
    }

    IIThing(IIThing&& other) noexcept :
        name(std::move(other.name)) {
    }

    IIThing& operator= (const IIThing&) = delete;
    IIThing& operator= (const IIThing&&) = delete;
    ~IIThing() = default;
};

class PermissiveContainer {
public:
    PermissiveContainer(const size_t& _value): value(_value) {}
    int getValue() {
        return value;
    }

private:
    int value;
};


class ExplicitContainer {
public:
    explicit ExplicitContainer(const size_t& _value): value(_value) {}
    int getValue() {
        return value;
    }

private:
    int value;
};

int IIThing::numConstructions = 0;
int IIThing::numCopies = 0;


TEST(InitializationAndIterationsTest, basic) {
    IIThing::resetCounts();

    std::vector<IIThing> things {IIThing{"Fred"}, IIThing{"Ted"}};

    std::string concat = "";
    for (const auto thing : things) {
        concat += thing.name;
    }

    EXPECT_STREQ("FredTed", concat.c_str());
    EXPECT_EQ(2, IIThing::numConstructions);
    EXPECT_EQ(4, IIThing::numCopies); // copied as passed into vector and in loop

    IIThing::resetCounts();

    concat = "";
    for (auto thing : things) {
        thing.name = thing.name+",";
        concat += thing.name;
    }

    EXPECT_STREQ("Fred,Ted,", concat.c_str());
    EXPECT_EQ(0, IIThing::numConstructions);
    EXPECT_EQ(2, IIThing::numCopies); // copied in loop
    EXPECT_STREQ("Fred", things.at(0).name.c_str());  // No change to the contents of the vector
    IIThing::resetCounts();

    concat = "";
    for (auto& thing : things) { // use an auto reference to be easy and avoid copies. Can't use const since we are going to decorate it
        thing.name = thing.name+",";
        concat += thing.name;
    }
    EXPECT_STREQ("Fred,Ted,", concat.c_str());
    EXPECT_EQ(0, IIThing::numConstructions);
    EXPECT_EQ(0, IIThing::numCopies);

    concat = "";
    for (const auto& thing : things) { // use an auto reference to be easy and avoid copies.
        concat += thing.name;
    }
    EXPECT_STREQ("Fred,Ted,", concat.c_str());  // yep the comma is still there
    EXPECT_EQ(0, IIThing::numConstructions);
    EXPECT_EQ(0, IIThing::numCopies);

}

TEST(InitializationAndIterationsTest, initializerWins) {
    std::vector<int> numbers(10, 1); // size, fill value
    EXPECT_EQ(1, numbers.at(9));

    std::vector<int> tenAndOne {10, 1};
    EXPECT_EQ(10, tenAndOne.at(0));
    EXPECT_EQ(1, tenAndOne.at(1));
    EXPECT_EQ(2, tenAndOne.size());
}

TEST(InitializationAndIterationsTest, convertingConstructor) {
    PermissiveContainer one(true);
    PermissiveContainer silly('a');
    EXPECT_EQ(1, one.getValue());
    EXPECT_EQ(97, silly.getValue());

    std::vector<PermissiveContainer> containers{1, true, false, 'a'};
    EXPECT_EQ(1, containers.at(0).getValue());
    EXPECT_EQ(1, containers.at(1).getValue());
    EXPECT_EQ(0, containers.at(2).getValue());
    EXPECT_EQ(97, containers.at(3).getValue());

    PermissiveContainer pc = 'b';
    EXPECT_EQ(98, pc.getValue());
}

TEST(InitializationAndIterationsTest, explicitConstructor) {
    ExplicitContainer one(true);
    ExplicitContainer silly('a');
    EXPECT_EQ(1, one.getValue());
    EXPECT_EQ(97, silly.getValue());

    // std::vector<ExplicitContainer> containers{1, true, false, 'a'};
    // no matching constructor

    // ExplicitContainer pc = 'b';
    // no viable conversion
}


