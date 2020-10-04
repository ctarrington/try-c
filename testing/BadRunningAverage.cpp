#include <cmath>
#include "BadRunningAverage.h"

int BadRunningAverage::push(int value) {
    if (this->count == 0) {
        this->average = value;
    } else {
        this->average = round((static_cast<float>(this->average) * static_cast<float>(this->count) + static_cast<float>(value) ) /
                                      static_cast<float>(this->count +1));
    }

    this->count++;
    return this->average;
}