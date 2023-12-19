/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 22:49:57 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/19 20:30:15 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <set>
#include <tuple>
#include <deque>
#include <vector>

enum e_value {
    ROW,
    COL,
    DELTAROW,
    DELTACOL,
};

bool inBound(int r, int c, int maxR, int maxC) {
    return r >= 0 && r < maxR && c >= 0 && c < maxC;
}

void printGrid(std::vector<std::string> grid) {
    for (size_t i = 0; i < grid.size(); i++)
        std::cout << grid[i] << std::endl;
}

int computeEnergized(std::tuple<int, int, int, int> pos, std::vector<std::string> grid) {
    std::set<std::tuple<int, int, int, int>> seen;
    std::deque<std::tuple<int, int, int, int>> path;
    std::tuple<int, int, int, int> cur = pos;
    path.push_back(cur);
    while (path.size() > 0) {
        cur = path.back();
        path.pop_back();
        std::get<ROW>(cur) += std::get<DELTAROW>(cur);
        std::get<COL>(cur) += std::get<DELTACOL>(cur);
        if (!inBound(std::get<ROW>(cur), std::get<COL>(cur), grid.size(), grid[0].size())) {
            continue ;
        }
        char c = grid[std::get<ROW>(cur)][std::get<COL>(cur)];
        if (c == '.' || 
            (c == '-' && std::get<DELTACOL>(cur) != 0) ||
            (c == '|' && std::get<DELTAROW>(cur) != 0)) {
            if (seen.find(cur) == seen.end()) {
                seen.insert(cur);
                path.push_back(cur);
            }
        }
        else if (c == '\\') {
            // 0, 1 -> 1, 0
            // 0, -1 -> -1, 0
            // 1, 0 -> 0, 1
            // -1, 0 -> 0, -1
            int tmp = std::get<DELTAROW>(cur);
            std::get<DELTAROW>(cur) = std::get<DELTACOL>(cur);
            std::get<DELTACOL>(cur) = tmp;
            if (seen.find(cur) == seen.end()) {
                seen.insert(cur);
                path.push_back(cur);
            }
        }
        else if (c == '/') {
            // 0, 1 -> -1, 0
            // 0, -1 -> 1, 0
            // 1, 0 -> 0, -1
            // -1, 0 -> 0, 1
            int tmp = std::get<DELTAROW>(cur);
            std::get<DELTAROW>(cur) = -std::get<DELTACOL>(cur);
            std::get<DELTACOL>(cur) = -tmp;
            if (seen.find(cur) == seen.end()) {
                seen.insert(cur);
                path.push_back(cur);
            }
        }
        else if (c == '|' && std::get<DELTAROW>(cur) == 0) {
            std::get<DELTACOL>(cur) = 0;
            std::get<DELTAROW>(cur) = 1;
            if (seen.find(cur) == seen.end()) {
                seen.insert(cur);
                path.push_back(cur);
            }
            std::get<DELTAROW>(cur) = -1;
            if (seen.find(cur) == seen.end()) {
                seen.insert(cur);
                path.push_back(cur);
            }
        }
        else if (c == '-' && std::get<DELTACOL>(cur) == 0) {
            std::get<DELTAROW>(cur) = 0;
            std::get<DELTACOL>(cur) = 1;
            if (seen.find(cur) == seen.end()) {
                seen.insert(cur);
                path.push_back(cur);
            }
            std::get<DELTACOL>(cur) = -1;
            if (seen.find(cur) == seen.end()) {
                seen.insert(cur);
                path.push_back(cur);
            }
        }
    }
    std::set<std::tuple<int, int>> energized;
    for (auto it = seen.begin(); it != seen.end(); it++) {
        std::tuple<int, int> tmp = {std::get<ROW>(*it), std::get<COL>(*it)};
        energized.insert(tmp);
    }
    return energized.size();
}

int main(void) {
    std::fstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return 1;
    }
    std::vector<std::string> grid;
    std::string line;
    while (std::getline(file, line))
        grid.push_back(line);
    
    int energized = 0;
    for (size_t i = 0; i < grid.size(); i++) {
        energized = std::max(energized, computeEnergized(std::make_tuple(i, -1, 0, 1), grid));
        energized = std::max(energized, computeEnergized(std::make_tuple(i, grid[0].size(), 0, -1), grid));
    }
    for (size_t i = 0; i < grid[0].size(); i++) {
        energized = std::max(energized, computeEnergized(std::make_tuple(-1, i, 1, 0), grid));
        energized = std::max(energized, computeEnergized(std::make_tuple(grid.size(), i, -1, 0), grid));
    }
    std::cout << "Energized: " << energized << std::endl;
}