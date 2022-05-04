//
// Created by visan on 5/1/22.
//

#ifndef CONNECT_FOUR_UTIL_H
#define CONNECT_FOUR_UTIL_H

namespace Connect_Four {
    //The number of players.
    const int NUM_COLORS = 2;
    //The height of the board.
    const int BOARD_HEIGHT = 6;
    //The width of the board.
    const int BOARD_WIDTH = 7;

    //The score to return from the evaluation function when a player made four in a row.
    const int WIN_SCORE = 10000;

    //Heuristic bonus score of three pieces in a row.
    const int THREE_ROW_SCORE = 10;

    //An infinite score, used in minimax.
    const int INFINITY = 100000000;


    enum Color {
        Red = 0,
        Yellow = 1,
    };

    inline Color get_opposite(Color x) {
        return (Color) (1 - x);
    }
}

#endif //CONNECT_FOUR_UTIL_H
