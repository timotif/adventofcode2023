/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:21:24 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/18 15:21:25 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

typedef unsigned char byte;

int hash(std::string s) {
    int ret = 0;
    for (std::string::iterator it = s.begin(); it != s.end(); ++it) {
        byte b = *it;
        ret += b;
        ret *= 17;
        ret %= 256;
    }
    return (ret);
}

int main(void) {
    std::fstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return (1);
    }
    std::vector<std::vector<std::string>> boxes(256);
    std::map<std::string, int> m;
    std::string s;
    while (std::getline(file, s, ',')) {
        if (s.find('-') != std::string::npos) {
            std::string label = s.substr(0, s.find('-'));
            int idx = hash(label);
            if (std::find(boxes[idx].begin(), boxes[idx].end(), label) != boxes[idx].end()) {
                boxes[idx].erase(std::find(boxes[idx].begin(), boxes[idx].end(), label));
            }
        }
        else {
            std::string label = s.substr(0, s.find('='));
            int value = std::stoi(s.substr(s.find('=') + 1));
            int idx = hash(label);
            if (std::find(boxes[idx].begin(), boxes[idx].end(), label) == boxes[idx].end())
                boxes[idx].push_back(label);
            m[label] = value;
        }
    }
    int total = 0;
    for (int i = 0; i < 256; ++i) {
        int fPower = 0;
        for (size_t it = 0; it < boxes[i].size(); it++) {
            fPower = (i + 1) * (it + 1) * m[boxes[i][it]];
            total += fPower;
        }
    }
    std::cout << total << std::endl;
}