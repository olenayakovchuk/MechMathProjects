#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T>
class Mediana {
public:
    static constexpr std::size_t MAX_CAPACITY = 100;

private:
    std::vector<T> items_;

public:
    Mediana() = default;

    Mediana(const T* arr, std::size_t count) {
        if (arr != nullptr && count > 0) {
            if (count > MAX_CAPACITY) {
                throw std::length_error("Exceeds maximum capacity of 100 elements.");
            }
            items_.assign(arr, arr + count);
        }
    }

    void push(const T& value) {
        if (items_.size() >= MAX_CAPACITY) {
            throw std::overflow_error("Mediana container is full (max 100 elements).");
        }
        items_.push_back(value);
    }

    // Видаляє та повертає n-й (1-based) елемент у впорядкованому порядку
    T pop(int n) {
        if (n < 1 || static_cast<std::size_t>(n) > items_.size()) {
            throw std::out_of_range("Index n is out of range in Mediana::pop.");
        }
        std::vector<T> sorted = items_;
        std::sort(sorted.begin(), sorted.end());
        T chosen = sorted[static_cast<std::size_t>(n - 1)];

        // Видаляємо перше входження вибраного елемента з поточної колекції
        auto it = std::find(items_.begin(), items_.end(), chosen);
        if (it != items_.end()) {
            items_.erase(it);
        }
        return chosen;
    }

    T mediana() const {
        if (items_.empty()) {
            throw std::runtime_error("Cannot compute median of an empty Mediana.");
        }
        std::vector<T> sorted = items_;
        std::sort(sorted.begin(), sorted.end());
        std::size_t sz = sorted.size();
        if (sz % 2 == 1) {
            return sorted[sz / 2];
        }
        return static_cast<T>((sorted[sz / 2 - 1] + sorted[sz / 2]) / 2);
    }

    std::size_t size() const noexcept {
        return items_.size();
    }
};

int main() {
    try {
        int init_vals[] = { 10, 2, 8, 4, 6 };
        Mediana<int> med(init_vals, 5);
        med.push(12);

        std::cout << "Current median: " << med.mediana() << "\n";
        int removed = med.pop(2);
        std::cout << "Popped 2nd smallest element: " << removed << "\n";
        std::cout << "New median: " << med.mediana() << "\n";

        // Перевірка винятку при виході за межі розміру
        med.pop(99);
    }
    catch (const std::exception& ex) {
        std::cout << "Caught expected exception: " << ex.what() << "\n";
    }
    return 0;
}