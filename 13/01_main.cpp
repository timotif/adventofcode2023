/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:07:13 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/13 17:07:14 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::string> rotateGrid(std::vector<std::string> const &grid) {
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

std::ostream &operator<<(std::ostream &os, const std::vector<std::string> &grid) {
    for (size_t i = 0; i < grid.size(); i++) {
        os << grid[i] << std::endl;
    }
    return (os);
}

int diffStr(std::string const &a, std::string const &b) {
    int ret = 0;
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i])
            ret++;
    }
    return (ret);
}

ssize_t findDiff(std::string const &a, std::string const &b) {
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i])
            return (i);
    }
    return (-1);
}

bool replaceCell(std::vector<std::string> &grid, size_t i, size_t j) {
    if (i < 0 || j < 0) {
        return (false);
    }
    if (grid[i][j] == '.')
        grid[i][j] = '#';
    else
        grid[i][j] = '.';
    return (true);
}

int findMirror(std::vector<std::string> &grid) {
    bool changed = false;
    for (size_t i = 0; i < grid.size() - 1; i++) {
        int diff = diffStr(grid[i], grid[i + 1]);
        if (diff <= 1) { // Found candidate
            bool valid = true;
            size_t curUp = i;
            size_t curDown = i + 1;
            std::vector<std::string> tmp = grid;
            while (1) {
                diff = diffStr(grid[curUp], grid[curDown]);
                size_t pos = findDiff(grid[curUp], grid[curDown]);
                if (diff == 1 && pos >= 0 && !changed) {
                    if (replaceCell(grid, curUp, pos)) {
                        changed = true;
                    }
                    continue ;
                }
                if (diff > 1) {
                    valid = false;
                    break ;
                }
                if (curUp <= 0 || curDown >= grid.size() - 1)
                    break ;
                curUp--;
                curDown++;
            }
            if (valid && changed)
                return (i + 1);
            else { // If after changing no valid match was found then revert
                grid = tmp;
                changed = false;
            }

        }
    }
    return (0);
}

int processGrid(std::vector<std::string> &grid) {
    std::vector<std::string> rGrid = rotateGrid(grid);
    return (findMirror(grid) * 100 + findMirror(rGrid));
}

int main(void) {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return (1);
    }
    std::string line;
    std::vector<std::string> grid;
    uint64_t total = 0;
    while (std::getline(file, line)) {
        if (!line.empty())
            grid.push_back(line);
        else {
            total += processGrid(grid);
            grid.clear();
            continue ;
        }
    }
    file.close();
    if (grid.size() > 0)
        total += processGrid(grid);
    std::cout << "Total: " << total << std::endl;
}