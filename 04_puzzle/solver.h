//
// Created by frak on 30.05.19.
//

#pragma once

#include "board.h"
#include <iostream>
#include <queue>

class solver {
private:
    size_t move_size;

    std::vector<board> solve_way;

    static std::pair<int, int> find_null_pos(board const& tmp_board);

    std::vector<board> ans_from_root;

    struct _weight_board {

        int munh;

        int dist_to_root;

        board brd;

        std::vector<board> _way_from_root;

        _weight_board(int dist, board const & brd, std::vector<board> &way_from_root);

        bool operator<(_weight_board const& t) const;
    };

public:
    std::vector<board>::iterator begin();

    std::vector<board>::iterator end();

    explicit solver(board const & temp_board);

    int moves() const;
};