/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 12:52:55 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/03 12:52:56 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>
#include <set>

void printMatrix(std::vector<std::vector<char>> matrix) {
    for (const auto& row : matrix) {
        for (char c : row) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool outOfBound(size_t row, size_t col, size_t nRows, size_t nCols) {
    if (row < 0 || col < 0 || row >= nRows || col >= nCols)
        return true;
    return false;
}

void printAround(std::vector<std::vector<char>> data, int col, int row) {
    int nRows = data.size();
    int nCols = data[0].size();
    for (int y = row - 1; y <= row + 1; y++) {
        for (int x = col - 1; x <= col + 1; x++) {
            if (!outOfBound(y, x, nRows, nCols)) {
                std::cout << data[y][x] << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void checkAround(std::vector<std::vector<char>> data, int x, int y, std::set<std::pair<int, int>> &nums) {

    for (int cur_y = y - 1; cur_y <= y + 1; cur_y++) {
        for (int cur_x = x - 1; cur_x <= x + 1; cur_x++) {
            if (outOfBound(cur_y, cur_x, data.size(), data[0].size()) || !std::isdigit(data[cur_y][cur_x]))
                continue ;
            // Found number around
            int num_x = cur_x;
            while (std::isdigit(data[cur_y][num_x - 1])) {
                num_x--;
            }
            nums.insert(std::make_pair(num_x, cur_y));
        }
    }
}

void printSet(std::set<std::pair<int, int>> nums) {
    for (auto n : nums) {
        std::cout << n.first << " " << n.second << std::endl;
    }
}

int main(void) {
    std::ifstream file("input.txt");
    std::string line;
    std::vector<std::vector<char>> table;
    std::set<std::pair<int, int>> nums;
    // Create matrix
    while (std::getline(file, line)) {
        std::vector<char> row;
        for (char c: line) {
            row.push_back(c);
        }
        table.push_back(row);
    }
    for (size_t j = 0; j < table.size(); j++) {
        for (size_t i = 0; i < table[j].size(); i++) {
            if (std::isdigit(table[j][i]) || table[j][i] == '.') // Scanning for symbols
                continue ;
            // Looking for adjacent numbers
            checkAround(table, i, j, nums);
        }
    }
    int total = 0;
    for (auto n : nums) {
        int num = 0;
        while (std::isdigit(table[n.second][n.first])) {
            num = num * 10 + (table[n.second][n.first] - '0');
            n.first++;
        }
        total += num;
    }
    std::cout << "Total: " << total << std::endl;
    file.close();
}