//
// Created by CT Arrington on 2020-04-08.
//

#ifndef ASYNCPROCESSING_OUTER_H
#define ASYNCPROCESSING_OUTER_H


#include "Inner.h"

class Outer {

public:
    Outer(Inner* inner_p);
    Inner inner;
    Inner* innerP;
};


#endif //ASYNCPROCESSING_OUTER_H
