//
// Created by frak on 30.05.19.
//

#include "board.h"
#include <iostream>
#include <queue>
#include "solver.h"
std::pair<int, int> solver::find_null_pos(board const& tmp_board)
{
    for (int i = 0; i < tmp_board.size(); i++)
    {
        for (int j = 0; j < tmp_board.size(); j++)
        {
            if (tmp_board[i][j] == 0)
            {
                return std::make_pair(i, j);
            }
        }
    }
}

solver::_weight_board::_weight_board(int dist, board const &in_brd, std::vector<board> &way_from_root)
{
    this->dist_to_root = dist;
    this->brd = in_brd;
    munh = in_brd.manhattan();
    this->_way_from_root = way_from_root;
}

bool solver::_weight_board::operator<(_weight_board const& t) const
{
    return (dist_to_root + munh) > (t.munh + t.dist_to_root);
}

std::vector<board>::iterator solver::begin() {
    return ans_from_root.begin();
}

std::vector<board>::iterator solver::end() {
        return ans_from_root.end();
}

solver::solver(board const & temp_board)
{
    if (!temp_board.is_solvable())
    {
        move_size = 0;
        return ;
    }
    std::priority_queue<_weight_board> prior_queue;
    std::vector<board> way_from_root;
    _weight_board first(0, temp_board, way_from_root);
    _weight_board last_kicked = first;
    prior_queue.push(first);
    while (!last_kicked.brd.is_goal())
    {
        last_kicked = prior_queue.top();
        last_kicked._way_from_root.push_back(last_kicked.brd);
        prior_queue.pop();
        auto pos = find_null_pos(last_kicked.brd);
        auto matrix = last_kicked.brd.get_data();
        if (pos.first != 0)
        {
            std::swap(matrix[pos.first][pos.second], matrix[pos.first - 1][pos.second]);
            prior_queue.push(_weight_board(last_kicked.dist_to_root + 1, board(matrix), last_kicked._way_from_root));
            std::swap(matrix[pos.first][pos.second], matrix[pos.first - 1][pos.second]);
        }
        if (pos.first != last_kicked.brd.size() - 1)
        {
            std::swap(matrix[pos.first][pos.second], matrix[pos.first + 1][pos.second]);
            prior_queue.push(_weight_board(last_kicked.dist_to_root + 1, board(matrix), last_kicked._way_from_root));
            std::swap(matrix[pos.first][pos.second], matrix[pos.first + 1][pos.second]);
        }
        if (pos.second != 0)
        {
            std::swap(matrix[pos.first][pos.second], matrix[pos.first][pos.second - 1]);
            prior_queue.push(_weight_board(last_kicked.dist_to_root + 1, board(matrix), last_kicked._way_from_root));
            std::swap(matrix[pos.first][pos.second], matrix[pos.first][pos.second - 1]);
        }
        if (pos.second != last_kicked.brd.size() - 1)
        {
            std::swap(matrix[pos.first][pos.second], matrix[pos.first][pos.second + 1]);
            prior_queue.push(_weight_board(last_kicked.dist_to_root + 1, board(matrix), last_kicked._way_from_root));
            std::swap(matrix[pos.first][pos.second], matrix[pos.first][pos.second + 1]);
        }
    }
    move_size = last_kicked.dist_to_root;
    ans_from_root = last_kicked._way_from_root;
}

int solver::moves() const { return move_size;}