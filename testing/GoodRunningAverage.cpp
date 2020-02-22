#include <cmath>

template<typename T>
GoodRunningAverage<T>::GoodRunningAverage() {
    static_assert(std::is_arithmetic<T>(), "Type must support addition and division.");
}

template<typename T>
T GoodRunningAverage<T>::push(T value) {
    this->total += value;
    this->count++;
    return round((float)this->total / (float)this->count);
}