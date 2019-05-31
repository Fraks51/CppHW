#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <random>
#include <ctime>

class board {
private:
    std::vector<std::vector<int>> data;
    std::mt19937 random_generator_;

    size_t _size;
public:
    board();

    explicit board(std::vector<std::vector<int>> &a);

    explicit board(size_t n);

    size_t size() const;

    int hamming() const;

    int manhattan() const;

    bool is_goal() const;

    bool is_solvable() const;

    bool operator==(board const& second) const;

    bool operator!=(board const& second) const;

    std::string to_string() const;

    std::vector<int> operator[](int i) const;

    std::vector<std::vector<int>> get_data() const;
};

#endif