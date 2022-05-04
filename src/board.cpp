//
// Created by visan on 5/1/22.
//

#include "board.h"

namespace Connect_Four {
    Board::Board() : piece(), height(), player_to_move() {
        reset();
    }

    void Board::reset() {
        player_to_move = Color::Yellow;
        for (int color = 0; color < NUM_COLORS; color++) {
            for (int line = 0; line < BOARD_HEIGHT; line++) {
                for (int column = 0; column < BOARD_WIDTH; column++) {
                    piece[color][line][column] = false;
                }
            }
        }

        for (int column = 0; column < BOARD_WIDTH; column++) {
            height[column] = 0;
        }
    }

    Color Board::current_player() const {
        return player_to_move;
    }

    bool Board::valid_move(unsigned column) const {
        return height[column] < BOARD_HEIGHT;
    }

    void Board::make_move(unsigned column) {
        assert(valid_move(column));

        unsigned &stack_height = height[column];
        piece[player_to_move][stack_height][column] = true;
        stack_height++;
        player_to_move = get_opposite(player_to_move);
    }

    void Board::undo_move(unsigned int column) {
        unsigned &stack_height = height[column];
        Color last = get_opposite(player_to_move);
        piece[last][stack_height - 1][column] = false;
        stack_height--;
        player_to_move = last;
    }

    long long Board::hash(Color color) {
        long long result = 0;
        long long current = 1;
        for (int line = 0; line < BOARD_HEIGHT; line++) {
            for (int column = 0; column < BOARD_WIDTH; column++) {
                if (piece[color][line][column]) {
                    result |= current;
                }
                current = current << 1;
            }
        }
        return result;
    }

    void Board::perft(unsigned int n, std::set<std::pair<long long, long long>> &hashes) {
        if (n == 0) {
            hashes.insert({hash(Color::Yellow), hash(Color::Red)});
            return;
        }
        if (score() != 0) {
            return;
        }

        for (int column = 0; column < BOARD_WIDTH; column++) {
            if (valid_move(column)) {
                make_move(column);
                perft(n - 1, hashes);
                undo_move(column);
            }
        }
    }

    bool Board::n_in_a_row(int n, int line, int column, Color color) const {
        int l = line, c = column;
        int count = 0;

        //Check vertical line.
        while (piece[color][l][c] && l < BOARD_HEIGHT) {
            count++;
            if (count == n)
                return true;
            l++;
        }

        l = line, c = column;
        count = 0;

        //Check horizontal line.
        while (piece[color][l][c] && c < BOARD_WIDTH) {
            count++;
            if (count == n)
                return true;
            c++;
        }
        l = line, c = column;
        count = 0;

        //Check anti-diagonal line.
        while (piece[color][l][c] && l < BOARD_HEIGHT && c >= 0) {
            count++;
            if (count == n)
                return true;
            l++;
            c--;
        }

        l = line, c = column;
        count = 0;
        //Check diagonal line.
        while (piece[color][l][c] && l < BOARD_HEIGHT && c < BOARD_WIDTH) {
            count++;
            if (count == n)
                return true;
            l++;
            c++;
        }
        return false;
    }


    int Board::score() const {
        int result = 0;
        for (int line = 0; line < BOARD_HEIGHT; line++) {
            for (int column = 0; column < BOARD_WIDTH; column++) {
                if (piece[Color::Yellow][line][column]) {
                    if (n_in_a_row(4, line, column, Color::Yellow))
                        return WIN_SCORE;
                    if (n_in_a_row(3, line, column, Color::Yellow)) {
                        result += THREE_ROW_SCORE;
                    }
                } else if (piece[Color::Red][line][column]) {
                    if (n_in_a_row(4, line, column, Color::Red))
                        return -WIN_SCORE;
                    if (n_in_a_row(3, line, column, Color::Red)) {
                        result -= THREE_ROW_SCORE;
                    }
                }

            }
        }
        return result;
    }

    bool Board::draw() const {
        for (int column = 0; column < BOARD_WIDTH; column++) {
            if (height[column] < BOARD_HEIGHT)
                return false;
        }
        return true;
    }

    void Board::load_board(const std::vector<std::string> &board) {
        reset();

        int pieces = 0;
        for (int line = BOARD_HEIGHT - 1; line >= 0; line--) {
            for (int column = 0; column < BOARD_WIDTH; column++) {
                if (board[line][column] == 'R') {
                    piece[Color::Red][BOARD_HEIGHT - 1 - line][column] = true;
                    pieces++;
                } else if (board[line][column] == 'Y') {
                    piece[Color::Yellow][BOARD_HEIGHT - 1 - line][column] = true;
                    pieces++;
                }
            }
        }
        if (pieces % 2 == 0) {
            player_to_move = Color::Yellow;
        } else {
            player_to_move = Color::Red;
        }
    }


    std::ostream &operator<<(std::ostream &os, const Board &board) {
        os << "Player to move: " << (board.player_to_move == Color::Yellow ? "Yellow" : "Red") << std::endl;
        for (int i = 0; i < BOARD_WIDTH; i++) {
            os << " " << i + 1 << " ";
        }
        os << std::endl;
        for (int line = BOARD_HEIGHT - 1; line >= 0; line--) {
            for (int column = 0; column < BOARD_WIDTH; column++) {
                if (board.piece[Color::Yellow][line][column]) {
                    os << " Y ";
                } else if (board.piece[Color::Red][line][column]) {
                    os << " R ";
                } else {
                    os << " # ";
                }
            }
            os << std::endl;
        }
        return os;
    }


}
