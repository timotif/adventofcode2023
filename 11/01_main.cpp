/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:16:42 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/11 19:17:11 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

void printMap(std::vector<std::vector<char>> map) {
    for (auto row : map) {
        for (auto col : row) {
            std::cout << col;
        }
        std::cout << std::endl;
    }
}

void printVecInt(std::vector<int> v) {
    for (auto i : v)
        std::cout << i << " ";
    std::cout << std::endl;
}

void initEmptyCol(std::vector<int> &c, int size) {
    for (int i = 0; i < size; i++)
        c.push_back(i);
}

int findDistance(std::pair<uint64_t, uint64_t> a, std::pair<uint64_t, uint64_t> b) {
    return ((a.first > b.first) ? (a.first - b.first) : (b.first - a.first)) + ((a.second > b.second) ? (a.second - b.second) : (b.second - a.second));
}

void printGalaxies(std::vector<std::pair<uint64_t, uint64_t>> galaxies) {
    for (auto g : galaxies)
        std::cout << "(" << g.first << ", " << g.second << ") ";
    std::cout << std::endl;
}

int main(void) {
    std::ifstream file("input.txt");
    std::string line;
    std::vector<std::vector<char>> map;
    std::vector<int> empty_row;
    std::vector<int> empty_col;
    std::vector<std::pair<uint64_t, uint64_t>> galaxies;
    int row = 0;
    int row_offset = 0;
    while (std::getline(file, line)) {
        std::vector<char> v(line.begin(), line.end());
        if (row == 0)
            initEmptyCol(empty_col, v.size());
        map.push_back(v);
        std::string::iterator it = line.begin();
        bool empty = true;
        while (it != line.end()) {
            if (*it == '#') {
                empty = false;
                std::vector<int>::iterator pos = std::find(empty_col.begin(), empty_col.end(), it - line.begin());
                if (pos != empty_col.end())
                    empty_col.erase(pos);
                galaxies.push_back(std::make_pair(it - line.begin(), row + row_offset));
            }
            it++;
        }
        if (empty) {
            row_offset += 999999;
            empty_row.push_back(row);
        }
        row++;
    }
    file.close();
    for (auto &g : galaxies) {
        int offset = 0;
        for (auto c : empty_col) {
            if ((uint64_t)c < g.first)
                offset += 999999;
            else
                break;
        }
        g.first += offset;
    }

    uint64_t total = 0;
    for (size_t i = 0; i < galaxies.size() - 1; i++) {
        for (size_t j = i + 1; j < galaxies.size(); j++) {
            int distance = findDistance(galaxies[i], galaxies[j]);
            total += distance;
        }
    }
    std::cout << "Total distance: " << total << std::endl;
}