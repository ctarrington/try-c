//
// Created by CT Arrington on 2020-04-08.
//

#include "Inner.h"

int Inner::counter = 0;

Inner::Inner() {
    index = Inner::counter++;
}
