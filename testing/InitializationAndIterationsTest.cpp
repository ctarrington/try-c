#include "gtest/gtest.h"

using namespace std;


class IIThing {

public:
    static int numConstructions;
    static int numCopies;

    static void resetCounts() {
        numCopies = 0;
        numConstructions = 0;
    }

    string name;

    IIThing(string _name) :
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

int IIThing::numConstructions = 0;
int IIThing::numCopies = 0;


TEST(InitializationAndIterationsTest, basic) {
    IIThing::resetCounts();

    vector<IIThing> things {IIThing{"Fred"}, IIThing{"Ted"}};

    string concat = "";
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
    vector<int> numbers(10, 1); // size, fill value
    EXPECT_EQ(1, numbers.at(9));

    vector<int> tenAndOne {10, 1};
    EXPECT_EQ(10, tenAndOne.at(0));
    EXPECT_EQ(1, tenAndOne.at(1));
    EXPECT_EQ(2, tenAndOne.size());
}



