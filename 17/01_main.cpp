/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 22:40:24 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/19 22:40:25 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <set>

enum e_value {
    HEAT,
    ROW,
    COL,
    DELTAROW,
    DELTACOL,
    STEPS,
};

void printGrid(std::vector<std::vector<int>> grid) {
    for (std::vector<int> row : grid) {
        for (int i : row)
            std::cout << i << " ";
        std::cout << std::endl;
    }
}

std::ostream &operator<<(std::ostream &os, std::tuple<int, int, int, int, int, int> const &t) {
    os << -std::get<HEAT>(t) << " " << std::get<ROW>(t) << " " << std::get<COL>(t) << " " << std::get<DELTAROW>(t) << " " << std::get<DELTACOL>(t) << " " << std::get<STEPS>(t);
    return os;
}

void extractTuple(std::tuple<int, int, int, int, int, int> &t, int &heat, int &row, int &col, int &deltaRow, int &deltaCol, int &steps) {
    heat = std::get<HEAT>(t);
    row = std::get<ROW>(t);
    col = std::get<COL>(t);
    deltaRow = std::get<DELTAROW>(t);
    deltaCol = std::get<DELTACOL>(t);
    steps = std::get<STEPS>(t);
}

bool inBound(int row, int col, int maxRow, int maxCol) {
    return row >= 0 && row < maxRow && col >= 0 && col < maxCol;
}

std::tuple<int, int, int, int, int> popHeat(std::tuple<int, int, int, int, int, int> &t) {
    int heat, row, col, deltaRow, deltaCol, steps;
    extractTuple(t, heat, row, col, deltaRow, deltaCol, steps);
    return {row, col, deltaRow, deltaCol, steps};
}

int main(void) {
    std::fstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return 1;
    }
    std::vector<std::vector<int>> grid;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        for (char c : line) {
            row.push_back(c - '0');
        }
        grid.push_back(row);
    }
    std::priority_queue<std::tuple<int, int, int, int, int, int>> pq;
    std::set<std::tuple<int, int, int, int, int>> seen;
    std::tuple<int, int, int, int, int, int> cur = {0, 0, 0, 0, 0, 0};
    pq.push(cur);
    while (!pq.empty()) {
        cur = pq.top();
        pq.pop();
        // End game
        if ((size_t)std::get<ROW>(cur) == grid.size() - 1 && (size_t)std::get<COL>(cur) == grid[0].size() - 1) {
            std::cout << "Heat loss: " << -std::get<HEAT>(cur) << std::endl;
            break ;
        }
        // Already visited
        if (seen.find(popHeat(cur)) != seen.end()) {
            continue ;
        }
        // Adding to visited without Heat Level
        seen.insert(popHeat(cur));
        int heat, row, col, deltaRow, deltaCol, steps;
        extractTuple(cur, heat, row, col, deltaRow, deltaCol, steps);
        if (steps < 10 && (deltaRow != 0 || deltaCol != 0)) {
            int newRow = row + deltaRow;
            int newCol = col + deltaCol;
            if (inBound(newRow, newCol, grid.size(), grid[0].size())) {
                pq.push({heat - grid[newRow][newCol], newRow, newCol, deltaRow, deltaCol, steps + 1});
            }
        }
        if (steps >= 4 || std::make_tuple(deltaRow, deltaCol) == std::make_tuple(0, 0)) {
            for (auto [newDeltaRow, newDeltaCol] : std::vector<std::tuple<int, int>>{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}) {
                if ((std::make_tuple(newDeltaRow, newDeltaCol) != std::make_tuple(deltaRow, deltaCol)) && (std::make_tuple(newDeltaRow, newDeltaCol) != std::make_tuple(-deltaRow, -deltaCol))) {
                    int newRow = row + newDeltaRow;
                    int newCol = col + newDeltaCol;
                    if (inBound(newRow, newCol, grid.size(), grid[0].size())) {
                        pq.push({heat - grid[newRow][newCol], newRow, newCol, newDeltaRow, newDeltaCol, 1});
                    }   
                }
            }
        }
    }
}