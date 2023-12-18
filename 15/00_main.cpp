/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:21:36 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/18 15:21:44 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

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
    int total = 0;
    std::string s;
    while (std::getline(file, s, ',')) {
        total += hash(s);
    }
    std::cout << total << std::endl;
}