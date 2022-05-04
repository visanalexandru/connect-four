//
// Created by visan on 5/4/22.
//

#ifndef CONNECT_FOUR_SEARCH_H
#define CONNECT_FOUR_SEARCH_H

#include"board.h"

namespace Connect_Four {
    class Search {
    private:
        Board &board;

        //Evaluate a given position by searching the tree.
        int negamax(int depth, int alpha, int beta);

        //Returns the score relative to the current side.
        int heuristic() const;

    public:
        explicit Search(Board &_board);

        //Returns the best move by searching until the given depth.
        int best_move(int depth);
    };

}


#endif //CONNECT_FOUR_SEARCH_H
