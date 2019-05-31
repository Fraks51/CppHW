//
// Created by frak on 29.05.19.
//

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include "board.h"

board::board()
{
    _size = 0;
}

board::board(std::vector<std::vector<int>> &a)
{
    data = a;
    _size = a.size();
}

board::board(const size_t n)
{
    std::vector<int> permutation(n * n);
    std::random_device device;
    random_generator_.seed(device());
    for (int i = 0; i < n * n; i++)
    {
        permutation[i] = i;
    }
    std::shuffle(permutation.begin(), permutation.end(), random_generator_);
    data.resize(n, std::vector<int>(n));
    for (int i = 0; i < n * n; i++)
    {
        data[i / n][i % n] = permutation[i];
    }
    _size = n;
}

size_t board::size() const
{
    return _size;
}

int board::hamming() const
{
    const size_t n = size();
    int counter = 0;
    for (int i = 0; i < n * n - 1; i++)
    {
        if (i + 1 != data[i / n][i % n])
        {
            counter++;
        }
    }
    if (data[n - 1][n - 1] != 0)
    {
        counter++;
    }
    return counter;
}

int board::manhattan() const
{
    const size_t n = size();
    std::vector<std::pair<int, int>> pos_in_board(n * n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            pos_in_board[data[i][j]] = std::make_pair(i, j);
        }
    }
    int counter = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j && i == n - 1)
            {
                counter += abs(i - pos_in_board[0].first);
                counter += abs(j - pos_in_board[0].second);
            } else {
                counter += abs(i - pos_in_board[n * i + j + 1].first);
                counter += abs(j - pos_in_board[n * i + j + 1].second);
            }
        }
    }
    return counter;
}

bool board::is_goal() const
{
    return hamming() == 0;
}

bool board::is_solvable() const
{
    int parity = 0;
    int n = size();
    int grid_width = n;
    int row = 0;
    int blank_row = 0;
    for (int i = 0; i < n * n; i++)
    {
        if (i % grid_width == 0) {
            row++;
        }
        if (data[i / n][i % n] == 0) {
            blank_row = row;
            continue;
        }
        for (int j = i + 1; j < n * n; j++)
        {
            if (data[i / n][i % n] > data[j / n][j % n] && data[j / n][j % n] != 0)
            {
                parity++;
            }
        }
    }
    if (grid_width % 2 == 0) {
        if (blank_row % 2 == 0)
        {
            return parity % 2 == 0;
        } else {
            return parity % 2 != 0;
        }
    } else {
        return parity % 2 == 0;
    }
}

bool board::operator==(board const& second) const
{
    return second.data == data;
}

bool board::operator!=(board const& second) const
{
    return second.data != data;
}

std::string board::to_string() const
{
    std::string str;
    for (auto const& tmp : data) {
        for (int i : tmp)
            str += std::to_string(i) + " ";
        str += "\n";
    }
    str += "\n";
    return str;
}

std::vector<int> board::operator[](int i) const {
    return data[i];
}

std::vector<std::vector<int>> board::get_data() const {
    return data;
}
