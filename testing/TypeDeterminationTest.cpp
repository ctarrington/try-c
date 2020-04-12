#include "gtest/gtest.h"
#include "Greeting.h"


// Meyers Item 4
template <typename T>
class ForTypeChecking;

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
    EXPECT_STREQ("NSt3__16vectorIiNS_9allocatorIiEEEE", typeid(numbers).name());

    auto cpi = numbers.cbegin();
    EXPECT_STREQ("NSt3__111__wrap_iterIPKiEE", typeid(cpi).name());

    int first = *cpi;
    EXPECT_EQ(1, first);
    EXPECT_STREQ("i", typeid(first).name());

}
