#ifndef TESTING_RUNNINGAVERAGE_H
#define TESTING_RUNNINGAVERAGE_H


class BadRunningAverage {
private:
    int average = 0;
    int count = 0;

public:
    int push(int value);
};

class GoodRunningAverage {
private:
    int total = 0;
    int count = 0;

public:
    int push(int value);
};

#endif //TESTING_RUNNINGAVERAGE_H
