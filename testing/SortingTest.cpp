#include <algorithm>

#include "gtest/gtest.h"

void swap(std::vector<int> &items, int index1, int index2) {
    std::swap(items[index1], items[index2]);
}

std::string join(const std::vector<int> &items) {
    std::string result;
    for (auto item : items) {
        if (!result.empty()) {
            result.append(",");
        }

        result.append(std::to_string(item));
    }

    return result;
}

std::vector<int> in_order() {
    return std::vector<int> {1,2,3,4,5,6,7,8,9,10};
}

std::vector<int> unsorted() {
    int items[] = {8,1,4,10,3,2,6,7,5,9};
    return std::vector<int> {8,1,4,10,3,2,6,7,5,9};
}

void bubble_sort(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
    bool swaps = true;
    auto current = begin;
    while (swaps) {
        swaps = false;
        while (current != end) {
            if (*current > *(current + 1)) {
                std::iter_swap(current, current + 1);
                swaps = true;
            }

            current++;
        }
        current = begin;
    }
}

TEST(SortingTest, swap) {
    std::vector<int> numbers = unsorted();
    swap(numbers, 2, 6);
    EXPECT_EQ(join(numbers), "8,1,6,10,3,2,4,7,5,9");
}

TEST(SortingTest, standard) {
    auto in_order_string = join(in_order());
    std::vector<int> numbers = unsorted();
    std::sort(numbers.begin(), numbers.end());
    EXPECT_EQ(join(numbers), in_order_string);
}

TEST(SortingTest, bubble) {
    auto in_order_string = join(in_order());
    std::vector<int> numbers = unsorted();
    bubble_sort(numbers.begin(), numbers.end());
    EXPECT_EQ(join(numbers), in_order_string);
}
