#include "gtest/gtest.h"
#include "Greeting.h"


// Meyers Item 4
template <typename T>
class ForTypeChecking;

class Thing {
public:
    static int copyCount;
    int id;

    Thing(int _id) {
        this->id = _id;
    }

    Thing(const Thing& person) {
        this->id = person.id;
        copyCount++;
    }
};

int Thing::copyCount = 0;

TEST(TypeDeterminationTest, compileTime) {
    auto x = 1;

    // uncomment to get compile time type info
    // ForTypeChecking<decltype(x)> xType;
}

TEST(TypeDeterminationTest, runTime) {
    // expected values will vary based on your compiler

    auto x = 1;
    const std::type_info* typeOfX = &typeid(x);

    EXPECT_STREQ("i", typeid(x).name());

    const int* pci = &x;
    EXPECT_STREQ("PKi", typeid(pci).name());

    const int* const cpci = &x;
    EXPECT_STREQ("PKi", typeid(cpci).name());

    auto y = 1L;
    EXPECT_STREQ("l", typeid(y).name());

    auto s = "hi there";
    EXPECT_STREQ("PKc", typeid(s).name());

    auto greetingP = new Greeting("Hi");
    EXPECT_STREQ("P8Greeting", typeid(greetingP).name());

    const Greeting cg = *greetingP;
    EXPECT_STREQ("8Greeting", typeid(cg).name());

    std::vector<int> numbers{1,2,3,4};
    EXPECT_EQ(1, numbers.at(0));
    string numbers_typename = typeid(numbers).name();
    EXPECT_TRUE( numbers_typename == "NSt3__16vectorIiNS_9allocatorIiEEEE" || numbers_typename == "St6vectorIiSaIiEE");

    auto cpi = numbers.cbegin();
    string cpi_typename = typeid(cpi).name();
    EXPECT_TRUE( cpi_typename == "NSt3__111__wrap_iterIPKiEE" || cpi_typename == "N9__gnu_cxx17__normal_iteratorIPKiSt6vectorIiSaIiEEEE");

    int first = *cpi;
    EXPECT_EQ(1, first);
    EXPECT_STREQ("i", typeid(first).name());

}

TEST(TypeDeterminationTest, autoIsBetter) {
    Thing* p1 = new Thing(1);
    Thing* p2 = new Thing(*p1);
    EXPECT_EQ(1, Thing::copyCount);
    EXPECT_EQ(1, p1->id);
    EXPECT_EQ(1, p2->id);
    p2->id = 55;
    EXPECT_EQ(1, p1->id);
    EXPECT_EQ(55, p2->id);

    auto things = std::vector<Thing>{Thing(2), Thing(3)};
    EXPECT_EQ(3, Thing::copyCount);  // copied into vector

    auto otherThings = std::vector<Thing>();
    const Thing& t10 = Thing(10);
    EXPECT_EQ(3, Thing::copyCount);

    otherThings.push_back(t10);
    EXPECT_EQ(4, Thing::copyCount); // copied into vector
    EXPECT_EQ(10, otherThings.at(0).id);
    otherThings.at(0).id = 66;
    EXPECT_EQ(66, otherThings.at(0).id);
    EXPECT_EQ(10, t10.id);


    auto itr = things.cbegin();
    auto thingP = itr;
    EXPECT_EQ(2, thingP->id);
    EXPECT_EQ(4, Thing::copyCount);  // no copy needed because we used cbegin and left things alone with auto

    thingP = next(itr);
    EXPECT_EQ(3, thingP->id);
    EXPECT_EQ(4, Thing::copyCount);  // no copy needed
}