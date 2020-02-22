#ifndef TESTING_BADRUNNINGAVERAGE_H
#define TESTING_BADRUNNINGAVERAGE_H


class BadRunningAverage {
private:
    int average = 0;
    int count = 0;

public:
    int push(int value);
};


#endif //TESTING_BADRUNNINGAVERAGE_H
