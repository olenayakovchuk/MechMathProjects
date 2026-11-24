#include <algorithm>
#include <iostream>
#include <vector>

static void print_vec(const char* label, const std::vector<int>& v) {
    std::cout << label;
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}

int main() {
    const std::vector<int> base = { 38, 12, 91, 5, 64, 23, 77, 16 };

    // 1. std::sort: повне сортування всього діапазону — O(N log N)
    std::vector<int> full = base;
    std::sort(full.begin(), full.end());
    print_vec("std::sort (full sorted):         ", full);

    // 2. std::partial_sort: сортує лише перші K найменших елементів — O(N log K)
    const std::size_t k = 3;
    std::vector<int> partial = base;
    std::partial_sort(partial.begin(), partial.begin() + static_cast<long>(k), partial.end());
    print_vec("std::partial_sort (first 3):     ", partial);

    // 3. std::nth_element: ставить k-й елемент на своє місце, ліворуч <= нього, праворуч >= — O(N)
    std::vector<int> nth = base;
    std::nth_element(nth.begin(), nth.begin() + static_cast<long>(k), nth.end());
    print_vec("std::nth_element (4th at idx 3): ", nth);

    std::cout << "\nConclusion: use partial_sort when you only need top-K ordered elements, "
        "and nth_element when you only need median/partitioning without full sort cost.\n";
    return 0;
}