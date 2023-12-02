/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 10:43:39 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/02 10:43:40 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <sstream>

enum e_color {
    RED,
    GREEN,
    BLUE
};

int main(void) {
    std::ifstream file("input.txt");
    std::string line;
    int total = 0;
    while (std::getline(file, line)) {
        std::cout << "Line: " << line << std::endl;
        line.erase(0, line.find(':') + 1);
        int colors[3] = {0, 0, 0};
        std::string round;
        std::stringstream ss(line);
        while (std::getline(ss, round, ';')) {
            std::string color;
            std::stringstream ss2(round);
            while (std::getline(ss2, color, ',')) {
                if (color.find("red") != std::string::npos) {
                    int red = std::stoi(color);
                    if (red > colors[RED])
                        colors[RED] = red;
                }
                if (color.find("green") != std::string::npos) {
                    int green = std::stoi(color);
                    if (green > colors[GREEN])
                        colors[GREEN] = green;
                }
                if (color.find("blue") != std::string::npos) {
                    int blue = std::stoi(color);
                    if (blue > colors[BLUE])
                        colors[BLUE] = blue;
                }
            }
        }
        total += colors[RED] * colors[GREEN] * colors[BLUE];
    }
    std::cout << "Total: " << total << std::endl;
}