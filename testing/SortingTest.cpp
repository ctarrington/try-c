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

std::vector<int> unsorted() {
    return std::vector<int> {81,112,41,110,13,22,0,56,17,15,18,91,1,2,3,4,5,81,0,110,11,13};
}

std::vector<int> in_order() {
   auto sorted = unsorted();
   std::sort(sorted.begin(), sorted.end());
   return sorted;
}

void run_sorts(void sort_function(std::vector<int>::iterator, std::vector<int>::iterator)) {
    std::vector<std::vector<int>> lists = {unsorted(), in_order()};

    for (auto list : lists) {
        auto sorted_copy = list;
        std::sort(sorted_copy.begin(), sorted_copy.end());

        sort_function(list.begin(), list.end());
        EXPECT_EQ(join(list), join(sorted_copy));
    }
}

void bubble_sort(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
    bool swaps = true;
    auto current = begin;
    while (swaps) {
        swaps = false;
        while (current < end) {
            if (*current > *(current + 1)) {
                std::iter_swap(current, current + 1);
                swaps = true;
            }

            current++;
        }
        current = begin;
    }
}

void selection_sort(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
    auto current = begin;
    while (current < end) {
        auto min = std::min_element(current, end);
        std::iter_swap(current, min);
        current++;
    }
}

TEST(SortingTest, swap) {
    std::vector<int> numbers = unsorted();
    swap(numbers, 2, 6);
    EXPECT_EQ(join(numbers), "81,112,0,110,13,22,41,56,17,15,18,91,1,2,3,4,5,81,0,110,11,13");
}

TEST(SortingTest, standard) {
    run_sorts(std::sort);
}

TEST(SortingTest, bubble) {
    run_sorts(bubble_sort);
}

TEST(SortingTest, selection) {
    run_sorts(selection_sort);
}
