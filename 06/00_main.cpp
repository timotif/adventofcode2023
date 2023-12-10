/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:42:18 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/06 20:42:19 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>

void printVector(std::vector<int> vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

int main(void) {
    std::ifstream file;
    file.open("input.txt");
    std::string line;
    std::vector<int> times;
    std::vector<int> distances;
    size_t numSize;
    std::getline(file, line);
    line = line.substr(line.find_first_of("0123456789"));
    while (line.size()) {
        times.push_back(std::stoi(line, &numSize));
        line = line.substr(numSize);
    }
    std::getline(file, line);
    line = line.substr(line.find_first_of("0123456789"));
    while (line.size()) {
        distances.push_back(std::stoi(line, &numSize));
        line = line.substr(numSize);
    }
    int res = 1;
    for (size_t i = 0; i < times.size(); i++) {
        int solutions = 0;
        for (int j = 1; j < times[i]; j++) {
            if ((times[i] - j) * j > distances[i]) {
                solutions++;
            }
        }
        std::cout << "Found " << solutions << " solutions" << std::endl;
        res *= solutions;
    }
    std::cout << "Result: " << res << std::endl;
}