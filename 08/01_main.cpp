/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 10:10:01 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/10 12:16:09 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <numeric>

void printMap(std::unordered_map<std::string, std::pair<std::string, std::string>> data) {
    for (auto it = data.begin(); it != data.end(); ++it) {
        std::cout << it->first << " => " << it->second.first << " " << it->second.second << std::endl;
    }
}

void printVec(std::vector<std::string> vec) {
    for (auto i : vec) {
        std::cout << i << std::endl;
    }
}

void printVecInt(std::vector<int> vec) {
    for (auto i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main(void) {
    std::ifstream in("input.txt");
    std::string line;
    std::string directions;
    std::unordered_map<std::string, std::pair<std::string, std::string>> data;
    std::getline(in, directions);
    while (std::getline(in, line)) {
        if (line.empty())
            continue;
        data[line.substr(0, 3)] = std::make_pair(
            line.substr(7, 3), line.substr(12, 3));
    }
    std::vector<std::string> pos;
    for (auto i : data) {
        if (i.first[2] == 'A')
            pos.push_back(i.first);
    }
    std::cout << "Starting positions: " << std::endl;
    printVec(pos);
    std::string::iterator it = directions.begin();
    std::vector<int> intervals;
    for (auto p : pos) {
        std::cout << "Computing path for " << p << std::endl;
        int count = 0;
        while (count == 0 or p[2] != 'Z') {
            if (it == directions.end())
                it = directions.begin();
            if (*it == 'L')
                p = data[p].first;
            else if (*it == 'R')
                p = data[p].second;
            else
                std::cout << "ERROR" << std::endl;
            it++;
            count++;
        }
        intervals.push_back(count);
        std::cout << "interval: " << intervals.back() << std::endl;
    }
    std::cout << "Intervals: " << std::endl;
    printVecInt(intervals);
    uint64_t count = intervals[0];
    for (size_t i = 1; i < intervals.size(); i++)
        count = std::lcm(count, intervals[i]);
    std::cout << count << std::endl;
}