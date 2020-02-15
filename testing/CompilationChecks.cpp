#include <iostream>

using namespace std;

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

}

void mutate(string *name_ptr) {
    name_ptr[2] = 'A';
}

void use_mutate() {
    const string const_name = "Fred";
    string name = "Ted";

    string* const const_ptr = &name;

    mutate(&name);
    mutate(const_ptr);
    // mutate(&const_name);  // cant pass a const to a mutating function
    cout << const_name << endl;
}

