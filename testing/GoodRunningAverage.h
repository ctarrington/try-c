#ifndef TESTING_GOODRUNNINGAVERAGE_H
#define TESTING_GOODRUNNINGAVERAGE_H

#include <cmath>

// include implementation in header to avoid linkage issues with templated class

template<typename T>
class GoodRunningAverage {
private:
    T total = 0;
    int count = 0;

public:
    GoodRunningAverage() {
        static_assert(std::is_arithmetic<T>(), "Type must support addition and division.");
    }

    GoodRunningAverage(const GoodRunningAverage&) = delete;
    GoodRunningAverage(const GoodRunningAverage&&) = delete;

    void operator=(const GoodRunningAverage&) = delete;
    void operator=(const GoodRunningAverage&&) = delete;


    T push(T value) {
        this->total += value;
        this->count++;
        return round((float)this->total / (float)this->count);
    }
};

#endif //TESTING_GOODRUNNINGAVERAGE_H
