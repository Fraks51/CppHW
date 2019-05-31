#include <iostream>
#include <cassert>
#include <queue>
#include "solver.h"

int main() {
    std::vector<std::vector<int>> test_board = {{3, 2, 8},
                                                {4, 5, 6},
                                                {7, 1, 0}};
    board b(test_board);
    assert(8 == b.manhattan());
    assert(1 == b.is_solvable());
    assert(3 == b.hamming());
    test_board = {{3, 2, 1},
                  {6, 5, 4},
                  {0, 8, 7}};
    board b2(test_board);
    assert(0 == b2.is_solvable());
    std::vector<std::vector<int>> test_board2 = {{1, 2, 3},
                                                {4, 0, 5},
                                                {7, 8, 6}};
    board solve_board(test_board2);
    solver s(solve_board);
    std::cout << s.moves() << "\n";
    for (const auto& t : s) {
        std::cout << t.to_string() << "\n";
    }
    return 0;
}
