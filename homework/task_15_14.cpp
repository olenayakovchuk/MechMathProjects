#include <iostream>
#include <limits>

class TicTacToe {
private:
    char board_[3][3]{};

public:
    TicTacToe() {
        reset();
    }

    void reset() {
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                board_[r][c] = ' ';
            }
        }
    }

    void draw() const {
        std::cout << "\n";
        for (int r = 0; r < 3; ++r) {
            std::cout << " " << board_[r][0] << " | " << board_[r][1] << " | " << board_[r][2] << " \n";
            if (r < 2) {
                std::cout << "---+---+---\n";
            }
        }
        std::cout << "\n";
    }

    bool place_mark(int row, int col, char symbol) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3) {
            return false;
        }
        if (symbol != 'X' && symbol != '0' && symbol != ' ') {
            return false;
        }
        if (symbol != ' ' && board_[row][col] != ' ') {
            return false;
        }
        board_[row][col] = symbol;
        return true;
    }

    bool player_move(char symbol, bool& quit_requested) {
        quit_requested = false;
        while (true) {
            std::cout << "Player '" << symbol << "' — enter row and col (1..3), or 0 0 to quit: ";
            int r = 0, c = 0;
            if (!(std::cin >> r >> c)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Try again.\n";
                continue;
            }
            if (r == 0 && c == 0) {
                quit_requested = true;
                return false;
            }
            if (place_mark(r - 1, c - 1, symbol)) {
                return true;
            }
            std::cout << "Cell occupied or out of range (1..3). Try again.\n";
        }
    }

    // Повертає: 'X' або '0' якщо є переможець, 'D' якщо нічия, ' ' якщо гра триває
    char check_state() const {
        for (int i = 0; i < 3; ++i) {
            if (board_[i][0] != ' ' && board_[i][0] == board_[i][1] && board_[i][1] == board_[i][2]) {
                return board_[i][0];
            }
            if (board_[0][i] != ' ' && board_[0][i] == board_[1][i] && board_[1][i] == board_[2][i]) {
                return board_[0][i];
            }
        }
        if (board_[0][0] != ' ' && board_[0][0] == board_[1][1] && board_[1][1] == board_[2][2]) {
            return board_[0][0];
        }
        if (board_[0][2] != ' ' && board_[0][2] == board_[1][1] && board_[1][1] == board_[2][0]) {
            return board_[0][2];
        }

        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                if (board_[r][c] == ' ') {
                    return ' ';
                }
            }
        }
        return 'D';
    }
};

int main() {
    TicTacToe game;
    game.draw();

    // Демонстраційна партія до перемоги 'X'
    const int demo_moves[5][3] = {
        {0, 0, 'X'},
        {1, 0, '0'},
        {0, 1, 'X'},
        {1, 1, '0'},
        {0, 2, 'X'}
    };

    for (const auto& m : demo_moves) {
        game.place_mark(m[0], m[1], static_cast<char>(m[2]));
        game.draw();
        char st = game.check_state();
        if (st == 'X' || st == '0') {
            std::cout << "Winner in demo match: " << st << "\n";
            break;
        }
        if (st == 'D') {
            std::cout << "Draw in demo match.\n";
            break;
        }
    }

    return 0;
}