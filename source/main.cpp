#include <iostream>
#include <vector>
#include <iterator>
using std::vector;

// template <typename T>
// void quicksort(vector<T>& vector) {
//     if (vector.size() == 1 || vector.size() == 0) {
//         return;
//     } else {
//         int pivot = 0;
//         auto middleValue = vector.size()
//     }
// }


template <typename T>
vector<T> merge(vector<T>& left, vector<T>& right) {
    auto leftIter = left.begin();
    auto rightIter = right.begin();
    vector<T> mergeVector;
    while (leftIter != left.end() || rightIter != right.end()) {
        if (*leftIter < *rightIter) {
            mergeVector.push_back(*leftIter);
            leftIter++;
        } else {
            mergeVector.push_back(*rightIter);
            rightIter++;
        }
    }

    return mergeVector;
}

template <typename T>
vector<T> mergesort(vector<T>& vector) {
    if (vector.size() == 0 || vector.size() == 1) {
        return vector;
    } else {
        size_t halfSize = (vector.size() / 2);
        typename std::vector<T>::const_iterator middle = vector.begin();
        std::advance(middle, halfSize);
        // auto a = std::vector<T>::iterator(middle);
        auto left = vector(vector.begin(), middle);
        auto right = vector(middle, vector.end());
        mergesort(left);
        mergesort(right);

        return merge(left, right);
    }
}

template <typename T>
void selectionsot(vector<T>& vector) {
    for (int i = 0; i < vector.size(); i++) {
        int smallestIndex = i;
        for (int j = i; j < vector.size(); j++) {
            if (vector[smallestIndex] > vector[j]) {
                smallestIndex = j;
            }
        }
        std::swap(vector[smallestIndex], vector[i]);
    }
}

//Referred to the book for help on algorithm.
template <typename T>
void insertionsort(T first, T last) {
    for (T next = first + 1; next < last; next++) {
        while (next != first && *next < *(next - 1)) {
            std::iter_swap(next, next - 1);
            --next;
        }
    }
}

int main() {
    vector<int> v = {4,8,1,3,54,12,456,1245};
    mergesort(v);
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << std::endl;
    }
}