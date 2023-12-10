/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 17:20:03 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/10 17:22:51 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <algorithm>
#define UP "S|F7"
#define DOWN "S|LJ"
#define LEFT "S-LF"
#define RIGHT "S-J7"

void printGrid(std::vector<std::string> grid) {
    for (auto line : grid) {
        std::cout << line << std::endl;
    }
    std::cout << std::endl;
}

void printSet(std::set<std::pair<int, int>> vec) {
    for (auto p : vec) {
        std::cout << "(" << p.first << ", " << p.second << ")" << " ";
    }
    std::cout << std::endl;
}

bool canGo(char c, std::string s) {
    for (auto ch : s)
        if (c == ch) return true;
    return (false);
}

bool connectsTo(char c, std::string s) {
    for (auto ch : s)
        if (c == ch) return true;
    return (false);
}

std::string find_s(std::string a, std::string b) {
    std::string res;
    for (auto ch : a) {
        if (b.find(ch) != std::string::npos) {
            res += ch;
        }
    }
    return (res);
}

void invalidToDot(std::vector<std::string> &grid, std::deque<std::pair<int, int>> path) {
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            if (std::find(path.begin(), path.end(), std::make_pair((int)i, (int)j)) == path.end())
                grid[i][j] = '.';
        }
    }
}

size_t unionSize(std::deque<std::pair<int, int>> a, std::set<std::pair<int, int>> b) {
    std::set<std::pair<int, int>> res;
    for (auto d : a) {
        res.insert(d);
    }
    for (auto d : b) {
        res.insert(d);
    }
    return (res.size());
}

int main(void) {
    std::ifstream file("input.txt");
    std::vector<std::string> grid;
    std::string line;
    while (std::getline(file, line)) {
        grid.push_back(line);
    }
    std::deque<std::pair<int, int>> path;
    std::set<std::pair<int, int>> visited;
    // Find starting point
    bool foundS = false;
    for (size_t i = 0; i < grid.size(); i++) {
        if (foundS) break ;
        for (size_t j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'S') {
                std::cout << "Found starting point at (" << j << ", " << i << ")" << std::endl;
                path.push_back(std::make_pair(i, j));
                foundS = true;
                break ;
            }
        }
    }
    // Checking movements
    std::string poss_s = "|-7JLF";
    for (size_t i = 0; i < path.size(); i++){
        uint32_t row = path[i].first;
        uint32_t col = path[i].second;
        if (poss_s.length() == 1) {
            grid[path.front().first][path.front().second] = poss_s[0];
        }
        if (col > 0 && connectsTo(grid[row][col], RIGHT) && canGo(grid[row][col - 1], LEFT) && visited.count(std::make_pair(row, col - 1)) == 0) {
            path.push_back(std::make_pair(row, col - 1));
            visited.insert(path[i]);
            if (grid[row][col] == 'S')
                poss_s = find_s(poss_s, RIGHT);
        }
        if (col < grid[0].length() - 1 && connectsTo(grid[row][col], LEFT) && canGo(grid[row][col + 1], RIGHT) && visited.count(std::make_pair(row, col + 1)) == 0) {
            path.push_back(std::make_pair(row, col + 1));
            visited.insert(path[i]);
            if (grid[row][col] == 'S')
                poss_s = find_s(poss_s, LEFT);
        }
        if (row > 0 && connectsTo(grid[row][col], DOWN) && canGo(grid[row - 1][col], UP) && visited.count(std::make_pair(row - 1, col)) == 0) {
            path.push_back(std::make_pair(row - 1, col));
            visited.insert(path[i]);
            if (grid[row][col] == 'S')
                poss_s = find_s(poss_s, DOWN);    
        }
        if (row < grid.size() - 1 && connectsTo(grid[row][col], UP) && canGo(grid[row + 1][col], DOWN) && visited.count(std::make_pair(row + 1, col)) == 0) {
            path.push_back(std::make_pair(row + 1, col));
            visited.insert(path[i]);
            if (grid[row][col] == 'S')
                poss_s = find_s(poss_s, UP);
        }
    }
    invalidToDot(grid, path);
    std::set<std::pair<int, int>> invalid;
    // Checking left to right
    for (size_t i = 0; i < grid.size(); i++) {
        std::string row = grid[i];
        bool valid = false;
        int up = -1;
        for (size_t j = 0; j < row.size(); j++) {
            char ch = row[j];
            if (ch == '|') { // moving to the right if I run into a | I have to cross
                valid = !valid;
            }
            else if (ch == '-' || ch == '.')   // moving to the right if I run into a - I just go on
                ;
            else if (ch == 'L' || ch == 'F') { // moving to the right if I run into an L I face up, F I face down
                assert(up == -1);
                up = (ch == 'L') ? 1 : 0;
            }
            else if (ch == '7' || ch == 'J') {
                if (ch == (up ? '7' : 'J')) {
                    valid = !valid;
                }
                up = -1;
            }
            else
                throw std::runtime_error("Invalid character");
            if (!valid) {
                std::pair<int, int> p = std::make_pair(i, j);
                invalid.insert(p);
            }
        }
    }

    int solution = (grid.size() * grid[0].size()) - unionSize(path, invalid);
    std::cout << "Solution: " << solution << std::endl;
}