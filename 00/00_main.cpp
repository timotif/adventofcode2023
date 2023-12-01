/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:58:53 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/01 16:59:18 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(void) {
    std::ifstream file("00_input.txt");
    std::string line;
    std::vector<int> digits;
    int total = 0;
    while (std::getline(file, line)) {
        digits.clear();
        for (std::string::iterator it = line.begin(); it != line.end(); it++) {
            if (std::isdigit(*it)) {
                digits.push_back((int)*it - '0');
            }
        }
        total += digits[0] * 10 + digits[digits.size() - 1];
    }
    file.close();
    std::cout << "Total: " << total << std::endl;
}