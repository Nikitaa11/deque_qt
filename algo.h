#pragma once
#include <deque>
#include <QString>

template<class T, class Comp>
std::deque<T> Merge(const std::deque<T>& half1, const std::deque<T>& half2, const Comp& comparator) {
    std::deque<T> result;
    auto it1 = half1.begin();
    auto it2 = half2.begin();

    while (it1 != half1.end() && it2 != half2.end()) {
        if (comparator(*it1, *it2)) {
            result.push_back(*it1++);
        } else {
            result.push_back(*it2++);
        }
    }

    while(it1 != half1.end()) {
        result.push_back(*it1++);
    }

    while (it2 != half2.end()) {
        result.push_back(*it2++);
    }

    return result;
}

template<class T>
std::deque<T> MergeSort(std::deque<T> src) {
    if (src.size() <= 1) {
        return src;
    }
    auto mid = src.size() / 2;
    std::deque<T> left(src.begin(), src.begin() + mid);
    std::deque<T> right(src.begin() + mid, src.end());

    auto defaultComparator = [](const T& a, const T& b){ return a < b; };

    return Merge(MergeSort(left), MergeSort(right), defaultComparator);
}

template<class T, class Comp>
std::deque<T> MergeSort(std::deque<T> src, const Comp& comparator) {
    if (src.size() <= 1) {
        return src;
    }
    auto mid = src.size() / 2;
    std::deque<T> left(src.begin(), src.begin() + mid);
    std::deque<T> right(src.begin() + mid, src.end());

    return Merge(MergeSort(left, comparator), MergeSort(right, comparator), comparator);
}
