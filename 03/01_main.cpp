/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 12:52:58 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/03 12:52:59 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>
#include <set>

bool outOfBound(size_t row, size_t col, size_t nRows, size_t nCols) {
    if (row < 0 || col < 0 || row >= nRows || col >= nCols)
        return true;
    return false;
}

bool checkAround(std::vector<std::vector<char>> data, int x, int y, std::set<std::pair<int, int>> &nums) {

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
    if (nums.size() == 2)
        return (true);
    return (false);
}

int findNumber(std::vector<std::vector<char>> table, int x, int y) {
    int num = 0;
    while (std::isdigit(table[y][x])) {
        num = num * 10 + (table[y][x] - '0');
        x++;
    }
    return num;
}

int main(void) {
    std::ifstream file("input.txt");
    std::string line;
    std::vector<std::vector<char>> table;
    // Create matrix
    while (std::getline(file, line)) {
        std::vector<char> row;
        for (char c: line) {
            row.push_back(c);
        }
        table.push_back(row);
    }
    int total = 0;
    for (size_t j = 0; j < table.size(); j++) {
        for (size_t i = 0; i < table[j].size(); i++) {
            std::set<std::pair<int, int>> nums;
            if (table[j][i] != '*') // Scanning for *
                continue ;
            // Looking for adjacent pair of numbers
            if (checkAround(table, i, j, nums)) {
                int gear = 1;
                for (auto n : nums) {
                    int num = findNumber(table, n.first, n.second);
                    gear *= num;
                }
                total += gear;
            }
        }
    }
    std::cout << "Total: " << total << std::endl;
    file.close();
}