#include <iostream>
#include "Generator.h"
#include "Inner.h"
#include "Outer.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    // Generator::init(100, 50);


    Inner* innerP = new Inner();
    std::cout << "innerP " << innerP->index << std::endl;

    Outer* outerP = new Outer(innerP);

    std::cout << "innerP " << innerP->index << std::endl;
    std::cout << "inner through outer " << outerP->inner.index << std::endl;

    outerP->inner.index = 33;
    outerP->innerP->index = 66;

    std::cout << "innerP " << innerP->index << std::endl;
    std::cout << "inner through outer " << outerP->inner.index << std::endl;

    return 0;
}