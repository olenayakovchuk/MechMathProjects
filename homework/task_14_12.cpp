#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

static std::string normalize_spaces(const std::string& line) {
    std::string result;
    bool in_space = true; // ігноруємо пробіли на початку рядка

    for (unsigned char ch : line) {
        if (std::isspace(ch)) {
            if (!in_space) {
                result.push_back(' ');
                in_space = true;
            }
        }
        else {
            result.push_back(static_cast<char>(ch));
            in_space = false;
        }
    }

    // Прибираємо можливий завершальний пробіл у кінці
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    return result;
}

int main() {
    int n = 0;
    std::cout << "Enter number of lines N: ";
    if (!(std::cin >> n) || n <= 0) {
        std::cerr << "Invalid N.\n";
        return 1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    const std::string filename = "lines_14_12.txt";
    {
        std::ofstream out(filename);
        if (!out.is_open()) {
            std::cerr << "Cannot create file.\n";
            return 1;
        }
        std::cout << "Enter " << n << " lines:\n";
        for (int i = 0; i < n; ++i) {
            std::string line;
            std::getline(std::cin, line);
            out << line << "\n";
        }
    }

    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Cannot reopen file.\n";
        return 1;
    }

    std::string normalized;
    std::string line;
    while (std::getline(in, line)) {
        normalized += normalize_spaces(line) + "\n";
    }
    in.close();

    std::ofstream out(filename, std::ios::trunc);
    if (!out.is_open()) {
        std::cerr << "Cannot overwrite file.\n";
        return 1;
    }
    out << normalized;
    std::cout << "Normalized " << n << " lines in " << filename << ".\n";
    return 0;
}