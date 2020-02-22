#include <cmath>
#include "BadRunningAverage.h"

int BadRunningAverage::push(int value) {
    if (this->count == 0) {
        this->average = value;
    } else {
        this->average = round(((float)this->average * (float) this->count + (float) value) /  (float) (this->count +1));
    }

    this->count++;
    return this->average;
}