/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:17:57 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/11 19:17:58 by tfregni          ###   ########.fr       */
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

int findDistance(std::pair<int, int> a, std::pair<int, int> b) {
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

void printGalaxies(std::vector<std::pair<int, int>> galaxies) {
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
    std::vector<std::pair<int, int>> galaxies;
    int row = 0;
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
                galaxies.push_back(std::make_pair(it - line.begin(), row));
            }
            it++;
        }
        if (empty)
            empty_row.push_back(row);
        row++;
    }
    file.close();
    // Expanding universe
    for (size_t i = 0; i < empty_row.size(); i++)
        map.insert(map.begin() + empty_row[i] + i, std::vector<char>(map[0].size(), '.'));
    for (size_t i = 0; i < empty_col.size(); i++)
        for (size_t j = 0; j < map.size(); j++)
            map[j].insert(map[j].begin() + empty_col[i] + i, '.');
    galaxies.clear();
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[0].size(); j++) {
            if (map[i][j] == '#')
                galaxies.push_back(std::make_pair(j, i));
        }
    }

    int total = 0;
    for (size_t i = 0; i < galaxies.size() - 1; i++) {
        for (size_t j = i + 1; j < galaxies.size(); j++) {
            int distance = findDistance(galaxies[i], galaxies[j]);
            total += distance;
        }
    }
    std::cout << "Total distance: " << total << std::endl;
}