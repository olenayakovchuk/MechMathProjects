/*
================================================================================
ЕКЗАМЕНАЦІЙНИЙ БІЛЕТ №13 - ТЕОРЕТИЧНЕ ПИТАННЯ
Тема: Потокове введення/виведення на C++. Робота з текстовими файлами на C++.
================================================================================

1. Потокове введення/виведення на C++:
У C++ введення/виведення (I/O) побудоване на концепції потоків (streams) —
послідовностей байтів або символів, які передаються між програмою та зовнішніми
пристроями (консоллю, файлами, рядками в пам'яті).

Основна ієрархія класів (бібліотека <iostream>):
- ios_base -> ios: базові класи, що керують станом потоку та форматуванням.
- istream: базовий клас для потоків введення (оператор >>, методи get, getline).
- ostream: базовий клас для потоків виведення (оператор <<, методи put, write).
- iostream: успадковує istream та ostream для двостороннього I/O.

Стандартні об'єкти потоків:
- std::cin  — стандартне введення (клавіатура, буферизований).
- std::cout — стандартне виведення (екран, буферизований).
- std::cerr — стандартний потік помилок (небуферизований).
- std::clog — потік для логування (буферизований).

Маніпулятори (<iomanip>):
Дозволяють керувати форматуванням даних у потоці:
- std::endl (перехід на новий рядок + скидання буфера flush), '\n'.
- std::setw(n) (ширина поля), std::setprecision(n) (точність дійсних чисел),
  std::fixed, std::scientific, std::left / std::right, std::boolalpha.

Стан потоку (прапори помилок):
- good() — потік готовий до роботи, помилок немає.
- eof()  — досягнуто кінця файлу (End-Of-File).
- fail() — логічна помилка (наприклад, очікувалось число, а ввели текст).
- bad()  — критична помилка читання/запису.
Для скидання прапорів використовується clear(), для очищення буфера — ignore().

2. Робота з текстовими файлами на C++:
Забезпечується заголовком <fstream>, який містить три основні класи:
- std::ifstream — потік для читання з файлу (input file stream).
- std::ofstream — потік для запису у файл (output file stream).
- std::fstream  — потік для одночасного читання та запису.

Режими відкриття файлів (std::ios::...):
- ios::in     — відкрити для читання (за замовчуванням для ifstream).
- ios::out    — відкрити для запису (за замовчуванням для ofstream).
- ios::trunc  — очистити файл, якщо він уже існує.
- ios::app    — дописувати в кінець файлу (append).
- ios::ate    — відкрити й перемістити вказівник у кінець файлу.

Основні етапи роботи з текстовим файлом:
1) Відкриття файлу через конструктор або метод open():
   std::ifstream in("matrix.txt");
2) Перевірка успішності відкриття:
   if (!in.is_open()) { ... }
3) Читання/запис даних:
   - Форматований ввід/вивід через оператори >> та << (роздільники — пробіли,
     табуляції, переноси рядків).
   - Порядкове читання через std::getline(in, line).
   - Посимвольне читання через in.get(ch).
4) Закриття файлу: відбувається автоматично в деструкторі (принцип RAII),
   або явно викликом close().
================================================================================
*/

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

bool parseStrictInt(const std::string& token, int& result) {
    try {
        std::size_t pos = 0;
        int value = std::stoi(token, &pos);
        if (pos != token.size()) {
            return false;
        }
        result = value;
        return true;
    }
    catch (...) {
        return false;
    }
}

bool parseStrictFiniteDouble(const std::string& token, double& result) {
    try {
        std::size_t pos = 0;
        double value = std::stod(token, &pos);
        if (pos != token.size() || !std::isfinite(value)) {
            return false;
        }
        result = value;
        return true;
    }
    catch (...) {
        return false;
    }
}

int main() {
    const std::string inputFilename = "matrix.txt";
    const std::string outputFilename = "transpose.txt";

    std::ifstream in(inputFilename);
    if (!in.is_open()) {
        std::cerr << "Error: cannot open input file '" << inputFilename << "'.\n";
        return 1;
    }

    // 1. Зчитуємо та перевіряємо розмір матриці n (1..20)
    std::string token;
    if (!(in >> token)) {
        std::cerr << "Error: input file is empty.\n";
        return 1;
    }

    int n = 0;
    if (!parseStrictInt(token, n) || n < 1 || n > 20) {
        std::cerr << "Error: invalid matrix size n (must be an integer in range 1..20).\n";
        return 1;
    }

    // 2. Зчитуємо та перевіряємо n * n скінченних дійсних чисел
    std::vector<std::vector<double>> matrix(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(in >> token)) {
                std::cerr << "Error: not enough elements in file (expected "
                    << (n * n) << " values).\n";
                return 1;
            }
            double val = 0.0;
            if (!parseStrictFiniteDouble(token, val)) {
                std::cerr << "Error: invalid or non-finite element '" << token
                    << "' at position (" << i << ", " << j << ").\n";
                return 1;
            }
            matrix[i][j] = val;
        }
    }

    // 3. Перевіряємо, чи немає зайвих непорожніх токенів
    if (in >> token) {
        std::cerr << "Error: unexpected extra token '" << token
            << "' after matrix data.\n";
        return 1;
    }

    in.close();

    // 4. Обчислюємо суми головної та побічної діагоналей
    double mainDiagSum = 0.0;
    double secondaryDiagSum = 0.0;
    for (int i = 0; i < n; ++i) {
        mainDiagSum += matrix[i][i];
        secondaryDiagSum += matrix[i][n - 1 - i];
    }

    // 5. Лише після повної перевірки створюємо вихідний файл і записуємо транспоновану матрицю
    std::ofstream out(outputFilename);
    if (!out.is_open()) {
        std::cerr << "Error: cannot create output file '" << outputFilename << "'.\n";
        return 1;
    }

    out << std::setprecision(10);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            out << matrix[j][i];
            if (j + 1 < n) {
                out << ' ';
            }
        }
        out << '\n';
    }
    out.close();

    std::cout << std::setprecision(10);
    std::cout << "Main diagonal sum: " << mainDiagSum << '\n';
    std::cout << "Secondary diagonal sum: " << secondaryDiagSum << '\n';
    std::cout << "Transposed matrix successfully written to '" << outputFilename << "'.\n";

    return 0;
}