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
    Person* personPtr;
    bool status;
};

PersonResult addEmployee(string name, int height) {
    Person* person = new Person(name, height);

    return {person, true};
}

TEST(DestructuringTests, Simple) {
    // decomposition requires C++17
    // auto [personPtr, status] = addEmployee("Fred", 66);
    PersonResult results = addEmployee("Fred", 66);

    EXPECT_TRUE(results.status);
    EXPECT_EQ("Fred", results.personPtr->getName());
    EXPECT_EQ(66, results.personPtr->getheight());
}

void mutate(Person mutant) {
    mutant.mutate();
}


TEST(DestructuringTests, MutationsPreventedByCopy) {
    // decomposition requires C++17
    // auto [personPtr, status] = addEmployee("Fred", 66);
    PersonResult results = addEmployee("Fred", 66);
    mutate(*results.personPtr);

    EXPECT_TRUE(results.status);
    EXPECT_EQ("Fred", results.personPtr->getName());
    EXPECT_EQ(66, results.personPtr->getheight());

    results.personPtr->mutate();
    EXPECT_EQ("ARRRRGGGHHHH", results.personPtr->getName());
    EXPECT_EQ(66*3, results.personPtr->getheight());

}
