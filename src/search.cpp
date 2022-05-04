//
// Created by visan on 5/4/22.
//

#include "search.h"

namespace Connect_Four {
    Search::Search(Board &_board) : board(_board) {

    }

    int Search::heuristic() const {
        int score = board.score();
        if (board.current_player() == Color::Red) {
            return -score;
        }
        return score;
    }

    int Search::negamax(int depth, int alpha, int beta) {
        if (board.draw()) {
            return 0;
        }

        int score = heuristic();
        if (score == WIN_SCORE || score == -WIN_SCORE) { // Check if it is a terminal node.
            return score;
        }

        if (depth == 0) {
            return score;
        }
        int value = -INFINITY;

        for (int column = 0; column < BOARD_WIDTH; column++) {
            if (board.valid_move(column)) {
                board.make_move(column);
                int next = -negamax(depth - 1, -beta, -alpha);
                board.undo_move(column);
                if (next > value) {
                    value = next;
                }
                if (value > alpha) {
                    alpha = value;
                }
                if (alpha >= beta) {
                    break;
                }
            }
        }
        return value;
    }

    int Search::best_move(int depth) {
        int best = -1, best_score = 0;
        for (int column = 0; column < BOARD_WIDTH; column++) {
            if (board.valid_move(column)) {
                board.make_move(column);
                int next = -negamax(depth - 1, -INFINITY, INFINITY);
                board.undo_move(column);
                if (best == -1 || next > best_score) {
                    best = column;
                    best_score = next;
                }
            }
        }
        return best;
    }
}