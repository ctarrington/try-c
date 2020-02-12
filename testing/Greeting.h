#ifndef TESTING_GREETING_H
#define TESTING_GREETING_H

#include <iostream>

using namespace std;

class Greeting {
    private: string prefix;

public:
    Greeting(string prefix);
    string sayHelloTo(string name);
};


#endif //TESTING_GREETING_H
