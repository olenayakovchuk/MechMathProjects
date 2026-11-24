#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

template <typename T>
class DynamicArray {
private:
    std::vector<T> data_;

    static void heapify(std::vector<T>& arr, std::size_t n, std::size_t root) {
        std::size_t largest = root;
        std::size_t left = 2 * root + 1;
        std::size_t right = 2 * root + 2;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }
        if (largest != root) {
            std::swap(arr[root], arr[largest]);
            heapify(arr, n, largest);
        }
    }

public:
    DynamicArray() = default;
    explicit DynamicArray(const std::vector<T>& values) : data_(values) {}

    static void heap_sort_inplace(std::vector<T>& arr) {
        std::size_t n = arr.size();
        if (n <= 1) {
            return;
        }
        for (std::size_t i = n / 2; i > 0; --i) {
            heapify(arr, n, i - 1);
        }
        for (std::size_t i = n; i > 1; --i) {
            std::swap(arr[0], arr[i - 1]);
            heapify(arr, i - 1, 0);
        }
    }

    void sort_heap() {
        heap_sort_inplace(data_);
    }

    void print() const {
        for (std::size_t i = 0; i < data_.size(); ++i) {
            std::cout << data_[i] << (i + 1 < data_.size() ? " " : "");
        }
        std::cout << "\n";
    }
};

int main() {
    DynamicArray<int> arr({ 42, 7, 19, 3, 25, 11 });
    std::cout << "Before heap sort: ";
    arr.print();

    arr.sort_heap();
    std::cout << "After heap sort : ";
    arr.print();
    return 0;
}