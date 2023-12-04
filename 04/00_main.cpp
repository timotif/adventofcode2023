/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:55:31 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/04 13:38:19 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

void printVec(std::vector<int> vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

typedef struct s_set {
    std::string line;
    std::vector<int> nums;
} t_set;

void lineToVec(t_set *set) {
    std::string::iterator it = set->line.begin();
    while (it != set->line.end()) {
        if (std::isdigit(*it)) {
            set->nums.push_back(std::stoi(set->line.substr(it - set->line.begin())));
            while(it != set->line.end() && std::isdigit(*it))
                it++;
        }
        else
            it++;
    }
}

int main(void) {
    std::ifstream file;
    std::string line;
    int total = 0;
    file.open("input.txt");
    while (std::getline(file, line)) {
        line.erase(0, line.find(':') + 2);
        std::cout << "Line: " << line << std::endl;
        t_set winners;
        t_set nums;
        winners.line = line.substr(0, line.find('|'));
        nums.line = line.substr(line.find('|') + 2);
        lineToVec(&winners);
        lineToVec(&nums);
        std::vector<int>::iterator itWin = winners.nums.begin();
        int res = 0;
        while (itWin != winners.nums.end()) {
            std::vector<int>::iterator itNum = nums.nums.begin();
            while (itNum != nums.nums.end()) {
                if (*itWin == *itNum) {
                    if (res == 0)
                        res++;
                    else
                        res *= 2;
                }
                itNum++;
            }
            itWin++;
        }
        total += res;
    }
    file.close();
    std::cout << "Total: " << total << std::endl;
}