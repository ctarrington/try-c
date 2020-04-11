//
// Created by CT Arrington on 2020-04-08.
//

#include "Outer.h"

Outer::Outer(Inner* inner_p) {
    innerP = inner_p;
    inner = *innerP;
}
