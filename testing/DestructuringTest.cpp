#include "gtest/gtest.h"

using namespace std;

class Person {

public:
    Person(string name, int height) {
        this->name = name;
        this->height = height;
    }

    string getName() {
        return name;
    }

    int getheight() {
        return height;
    }

private:
    string name;
    int height;
};

struct PersonResult {
    Person* person;
    bool success;
};

PersonResult addEmployee(string name, int height) {
    Person* person = new Person(name, height);

    return {person, true};
}

TEST(DestructuringTests, Simple) {
    auto [personPtr, status] = addEmployee("Fred", 66);

    EXPECT_TRUE(status);
    EXPECT_EQ("Fred", personPtr->getName());
    EXPECT_EQ(66, personPtr->getheight());
}
