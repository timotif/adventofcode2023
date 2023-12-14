/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:35:25 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/14 12:35:26 by tfregni          ###   ########.fr       */
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

void roll(std::string &line, ssize_t pos) {
    assert (line[pos] == 'O');
    while (pos - 1 >= 0 && line[pos - 1] == '.') {
        pos--;
        line[pos + 1] = '.';
        line[pos] = 'O';
        assert (pos >= 0);
        assert ((size_t)pos < line.size());
    }
}
int calcLoad(std::vector<std::string> const &platform) {
    int total = 0;
    std::vector<std::string> rPlatform = rotateGridCCW(platform);
    for (size_t i = 0; i < rPlatform.size(); i++) {
        int subtotal = std::count(rPlatform[i].begin(), rPlatform[i].end(), 'O');
        total += subtotal * (i + 1);
    }
    return (total);
}

void runCycle(std::vector<std::string> &platform) {
    for (int tilt = 0; tilt < 4; tilt++) {
        for (size_t i = 0; i < platform.size(); i++) {
            for (size_t j = 0; j < platform[i].size(); j++) {
                if (platform[i][j] == 'O') {
                    roll(platform[i], j);
                }
            }
        }
        platform = rotateGridCW(platform);
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
    std::vector<std::vector<std::string>> seen;
    std::vector<int> loads;
    int count = 0;
    while (1) { // looking for a repetition
        runCycle(platform);
        if (std::find(seen.begin(), seen.end(), platform) != seen.end()) {
            break ;
        }
        seen.push_back(platform);
        loads.push_back(calcLoad(platform));
        count++;
    }
    int first_seen = std::find(seen.begin(), seen.end(), platform) - seen.begin();
    int total = loads.at(
        (1000000000 - 1 - first_seen) % // -1 to account for counting cycles from 0
        (count - first_seen) + first_seen 
    );

    std::cout << "Total: " << total << std::endl;
}