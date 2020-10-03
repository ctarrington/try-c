#ifndef TESTING_GREETING_H
#define TESTING_GREETING_H

#include <iostream>

class Greeting {

private:
    std::string prefix;

public:
    Greeting(std::string prefix);
    std::string sayHelloTo(std::string name);
};


#endif //TESTING_GREETING_H
