/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:42:20 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/06 20:42:21 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>

void printVector(std::vector<uint64_t> vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

int main(void) {
    std::ifstream file;
    file.open("input.txt");
    std::string line;
    std::vector<uint64_t> times;
    std::vector<uint64_t> distances;
    std::getline(file, line);
    line = line.substr(line.find_first_of("0123456789"));
    line.erase(std::remove_if(line.begin(), line.end(), [](char c) { return std::isspace(c); }), line.end());
    times.push_back(std::stoll(line));
    std::getline(file, line);
    line = line.substr(line.find_first_of("0123456789"));
    line.erase(std::remove_if(line.begin(), line.end(), [](char c) { return std::isspace(c); }), line.end());
    distances.push_back(std::stoll(line));
    int res = 1;
    for (size_t i = 0; i < times.size(); i++) {
        int solutions = 0;
        for (uint64_t j = 0; j < times[i]; j++) {
            if ((times[i] - j) * j > distances[i]) {
                solutions++;
            }
        }
        std::cout << "Found " << solutions << " solutions" << std::endl;
        res *= solutions;
    }
    std::cout << "Result: " << res << std::endl;
}