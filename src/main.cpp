#include <iostream>
#include"board.h"
#include"search.h"

using namespace std;


int read_move(Connect_Four::Board &board) {
    int move = 0;
    bool valid = false;
    while (!valid) {
        while (move < 1 || move > Connect_Four::BOARD_WIDTH) {
            cout << "Enter your move (number between 1 and 7):";
            cin >> move;
        }
        valid = board.valid_move(move - 1);
    }
    return move - 1;
}

Connect_Four::Color read_color() {
    int color;
    do {
        cout << "1. Play as yellow" << endl;
        cout << "2. Play as red" << endl;
        cin >> color;
    } while (color < 1 || color > 2);
    if (color == 1) {
        return Connect_Four::Color::Yellow;
    }
    return Connect_Four::Color::Red;
}

int main() {
    Connect_Four::Board board;
    Connect_Four::Search search(board);
    Connect_Four::Color current = read_color();

    while (board.score() != -Connect_Four::WIN_SCORE && board.score() != Connect_Four::WIN_SCORE) {
        cout << board << endl;
        if (board.current_player() == current) {
            board.make_move(read_move(board));
        } else {
            board.make_move(search.best_move(10));
        }
    }

    cout << board << endl;
    if (board.current_player() == Connect_Four::Color::Yellow) {
        cout << "Red wins";
    } else {
        cout << "Yello wins";
    }

    return 0;
}
