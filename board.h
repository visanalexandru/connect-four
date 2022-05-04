//
// Created by visan on 5/1/22.
//

#ifndef CONNECT_FOUR_BOARD_H
#define CONNECT_FOUR_BOARD_H

#include<iostream>
#include<cassert>
#include<set>
#include<vector>
#include"util.h"

namespace Connect_Four {
    //This class implements the functionality of a connect-four board.
    class Board {
    private:
        //piece[color][line][column] is true if a piece of the given color is at the given position.
        bool piece[NUM_COLORS][BOARD_HEIGHT][BOARD_WIDTH];

        //height[column] represents the height of the stack at the given column.
        unsigned height[BOARD_WIDTH];

        //The current player to move.
        Color player_to_move;

        long long hash(Color color);

        //Check if there are n pieces of the given color in a row starting with the given position.
        bool n_in_a_row(int n, int line, int column, Color color) const;


    public:
        Board();

        //Clear the board and set the current player to move to yellow.
        void reset();

        //Gets the current player to move.
        Color current_player() const;

        //Checks if the current player can place a piece in the given stack
        bool valid_move(unsigned column) const;

        //The current player places a piece in the given stack.
        void make_move(unsigned column);

        //Undo the move at the given column.
        void undo_move(unsigned column);

        //Outputs the board information to the given ostream.
        friend std::ostream &operator<<(std::ostream &os, const Board &board);

        //Computes the number of different positions after n plies.
        void perft(unsigned n, std::set<std::pair<long long, long long>> &hashes);

        //Scores the current board.
        int score() const;

        //Checks if the game is drawn.
        bool draw() const;

        //Sets up a new board from the given list of strings.
        void load_board(const std::vector<std::string> &board);
    };

    std::ostream &operator<<(std::ostream &os, const Board &board);
}


#endif //CONNECT_FOUR_BOARD_H
