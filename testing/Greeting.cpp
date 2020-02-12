#include "Greeting.h"

Greeting::Greeting(string prefix) {
    this->prefix = prefix;
}

string Greeting::sayHelloTo(string name) {
    return this->prefix + ", " + name;
}