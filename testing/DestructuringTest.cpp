#include "gtest/gtest.h"

using namespace std;

class Person {

public:
    Person(string name, int height) {
        this->name = name;
        this->height = height;
    }

    Person(const Person&) = default;
    Person& operator=(const Person&) = default;

    string getName() {
        return name;
    }

    int getheight() {
        return height;
    }

    void mutate() {
        this->name = "ARRRRGGGHHHH";
        this->height *= 3;
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

void mutate(Person mutant) {
    mutant.mutate();
}


TEST(DestructuringTests, MutationsPrevetedByCopy) {
    auto [personPtr, status] = addEmployee("Fred", 66);
    mutate(*personPtr);

    EXPECT_TRUE(status);
    EXPECT_EQ("Fred", personPtr->getName());
    EXPECT_EQ(66, personPtr->getheight());

    personPtr->mutate();
    EXPECT_EQ("ARRRRGGGHHHH", personPtr->getName());
    EXPECT_EQ(66*3, personPtr->getheight());

}
