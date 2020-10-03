#include <iostream>

class ImportantResource {
public:
    ImportantResource() {

    }

    ImportantResource(const ImportantResource&) = delete;
    ImportantResource& operator=(const ImportantResource&) = delete;
};

void foo() {
    const int const_int = 1;
    // const_int = 2;

    int a = 1;
    int b = 1;

    const int* pointer_to_const_int = &a;
    // *pointer_to_const_int = 2;
    pointer_to_const_int = &b;

    int* const const_pointer_to_int = &a;
    *const_pointer_to_int = 2;
    // const_pointer_to_int = &b;

    const int* const const_pointer_to_const_int = &a;
    // *const_pointer_to_const_int = 2;
    // const_pointer_to_const_int = &b;

    const int& reference_to_const_int = 10;
    // reference_to_const_int = 11;
    int& liberated_reference_to_int = const_cast<int&>(reference_to_const_int);
    liberated_reference_to_int = 11;
}

void mutate(std::string *name_ptr) {
    name_ptr[2] = 'A';
}

void use_mutate() {
    const std::string const_name = "Fred";
    std::string name = "Ted";

    std::string* const const_ptr = &name;

    mutate(&name);
    mutate(const_ptr);
    // mutate(&const_name);  // cant pass a const to a mutating function
    std::cout << const_name << std::endl;
}

auto resource1_ptr = new ImportantResource();
//auto resource1 = *resource1_ptr;   // compilation error

namespace Outer {
    namespace Inner {
        int add(int a, int b) {
            return a+b;
        }
    }
}

int sum = Outer::Inner::add(1,2);
// int nope = add(1,2);


