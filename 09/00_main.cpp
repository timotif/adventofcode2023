/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:27:06 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/09 16:42:21 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>

void printVec(std::vector<int> &v) {
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

int allZeros(std::vector<int> &v) {
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] != 0) {
            return (0);
        }
    }
    return (1);
}

int compute(std::vector<int> &v) {
    std::vector<int> next;
    bool end = true;
    for (size_t i = 0; i < v.size() - 1; i++) {
        int diff = v[i + 1] - v[i];
        next.push_back(diff);
        if (diff != 0)
            end = false;
    }
    if (end)
        return (v.back());
    v.push_back(v.back() + compute(next));
    return (v.back());
}

int main(void) {
    std::ifstream file;
    file.open("input.txt");
    std::string line;
    int sum = 0;
    while (std::getline(file, line)) {
        std::vector<int> v;
        while (line.find(" ") != std::string::npos) {
            v.push_back(std::stoi(line));
            line = line.substr(line.find(" ") + 1);
        }
        v.push_back(std::stoi(line));
        sum += compute(v);  
    }
    std::cout << "Sum: " << sum << std::endl;
}