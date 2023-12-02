/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:58:49 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/02 10:37:04 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(void) {
    std::ifstream file("input.txt");
    std::string line;
    std::vector<int> digits;
    std::string numbers[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int total = 0;
    while (std::getline(file, line)) {
        digits.clear();
        std::cout << "Line: " << line << std::endl;
        for (std::string::iterator it = line.begin(); it != line.end(); it++) {
            if (std::isdigit(*it)) {
                digits.push_back((int)*it - '0');
            }
            for (int i = 0; i < 10; i++) {
                if (!line.compare(std::distance(line.begin(), it), numbers[i].size(), numbers[i])) {
                    digits.push_back(i);
                }
            }
        }
        total += digits[0] * 10 + digits[digits.size() - 1];
    }
    file.close();
    std::cout << "Total: " << total << std::endl;
}