/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 10:59:13 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/14 10:59:14 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>

std::vector<std::string> rotateGridCW(std::vector<std::string> const &grid) {
    std::vector<std::string> ret;
    for (size_t j = 0; j < grid[0].size(); j++) {
        std::string line;
        for (size_t i = grid.size() - 1; i < grid.size(); i--) {
            line += grid[i][j];
        }
        ret.push_back(line);
    }
    return (ret);
}

std::vector<std::string> rotateGridCCW(std::vector<std::string> const &grid) {
    std::vector<std::string> ret;
    for (ssize_t j = grid[0].size() - 1; j >= 0; j--) {
        std::string line;
        for (size_t i = 0; i < grid.size(); i++) {
            line += grid[i][j];
        }
        ret.push_back(line);
    }
    return (ret);
}

std::ostream &operator<<(std::ostream &os, const std::vector<std::string> &grid) {
    for (size_t i = 0; i < grid.size(); i++) {
        os << grid[i] << std::endl;
    }
    return (os);
}

void roll(std::string &line, size_t pos) {
    assert (line[pos] == 'O');
    while (--pos >= 0 && line[pos] == '.') {
        line[pos + 1] = '.';
        line[pos] = 'O';
    }
}

int main(void) {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::string> platform;
    while (std::getline(file, line))
        platform.push_back(line);
    platform = rotateGridCCW(platform);
    for (size_t i = 0; i < platform.size(); i++) {
        for (size_t j = 0; j < platform[i].size(); j++) {
            if (platform[i][j] == 'O') {
                roll(platform[i], j);
            }
        }
    }
    int total = 0;
    platform = rotateGridCCW(platform);
    for (size_t i = 0; i < platform.size(); i++) {
        int subtotal = std::count(platform[i].begin(), platform[i].end(), 'O');
        total += subtotal * (i + 1);
    }
    std::cout << "Total: " << total << std::endl;
}