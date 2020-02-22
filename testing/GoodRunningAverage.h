#ifndef TESTING_GOODRUNNINGAVERAGE_H
#define TESTING_GOODRUNNINGAVERAGE_H

template<typename T>
class GoodRunningAverage {
private:
    T total = 0;
    int count = 0;

public:
    GoodRunningAverage();
    GoodRunningAverage(const GoodRunningAverage&) = delete;
    GoodRunningAverage(const GoodRunningAverage&&) = delete;

    void operator=(const GoodRunningAverage&) = delete;
    void operator=(const GoodRunningAverage&&) = delete;


    T push(T value);
};

// include the implementation so the generated template methods are linked
#include "GoodRunningAverage.cpp"


#endif //TESTING_GOODRUNNINGAVERAGE_H
