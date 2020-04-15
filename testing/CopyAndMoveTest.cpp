#include <utility>

#include "gtest/gtest.h"
#include "Greeting.h"


class Thingy {
public:
    static int copyCount;
    static int moveCount;

    string name;
    int id;

    Thingy(int _id, string _name) {
        this->id = _id;
        this->name = _name;
    }

    Thingy(const Thingy& person) {
        this->id = person.id;
        this->name = person.name;
        copyCount++;
    }

    // never const
    Thingy(Thingy&& person) {
        this->id = person.id;
        person.id = 0;
        this->name = std::move(person.name);
        moveCount++;
    }
};

int Thingy::copyCount = 0;
int Thingy::moveCount = 0;

void resetCounts() {
    Thingy::copyCount = 0;
    Thingy::moveCount = 0;
}

TEST(CopyAndMoveTest, copy) {
    resetCounts();

    Thingy t1(1, "one");
    Thingy t2 = t1;

    t1.name = "oooooneeee";
    EXPECT_STREQ("oooooneeee", t1.name.c_str());
    EXPECT_STREQ("one", t2.name.c_str());

    EXPECT_EQ(1, Thingy::copyCount);
    EXPECT_EQ(0, Thingy::moveCount);
}


TEST(CopyAndMoveTest, move) {
    resetCounts();

    Thingy t1(1, "one");
    Thingy t2 = std::move(t1);

    EXPECT_STREQ("", t1.name.c_str());
    EXPECT_STREQ("one", t2.name.c_str());

    EXPECT_EQ(0, Thingy::copyCount);
    EXPECT_EQ(1, Thingy::moveCount);
}

TEST(CopyAndMoveTest, moveString) {
    string one = "one";

    string s = std::move(one);
    EXPECT_STREQ("one", s.c_str());
    EXPECT_STREQ("", one.c_str());
}




