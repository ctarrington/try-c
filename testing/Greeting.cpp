#include "Greeting.h"

Greeting::Greeting(std::string prefix) {
    this->prefix = prefix;
}

std::string Greeting::sayHelloTo(std::string name) {
    return this->prefix + ", " + name;
}