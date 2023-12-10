/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 10:10:01 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/10 10:10:17 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <unordered_map>

void printMap(std::unordered_map<std::string, std::pair<std::string, std::string>> data) {
    for (auto it = data.begin(); it != data.end(); ++it) {
        std::cout << it->first << " => " << it->second.first << " " << it->second.second << std::endl;
    }
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
    std::string::iterator it = directions.begin();
    int count = 0;
    std::string pos = "AAA";
    while (pos != "ZZZ") {
        if (it == directions.end())
            it = directions.begin();
        if (*it == 'L')
            pos = data[pos].first;
        else if (*it == 'R')
            pos = data[pos].second;
        else
            std::cout << "ERROR" << std::endl;
        count++;
        it++;
    }
    std::cout << count << std::endl;
}