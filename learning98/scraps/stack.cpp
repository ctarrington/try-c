#include "stack.h"

namespace Stack {
    const int max_size = 200;
    char v[max_size];
    int top = 0;
}

void Stack::push(char c) {
    if (top < max_size) {
        v[top] = c;
        top++;
    } else {
        throw Overflow();
    }
}

char Stack::pop() {
    if (top >= 0) {
        top--;
        return v[top];
    }

    return 0;
}
