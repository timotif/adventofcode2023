#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

enum e_color {
    RED,
    GREEN,
    BLUE
};

int main(void) {
    int reference[3] = {12, 13, 14};
    std::ifstream file("input.txt");
    int total = 0;
    std::string line;
    int game = 1;
    while (std::getline(file, line)) { // GAME LOOP
        std::cout << "Line: " << line << std::endl;
        line.erase(0, line.find(':') + 1);
        std::string round;
        std::stringstream ss(line);
        bool validGame = true;
        while (validGame && std::getline(ss, round, ';')) { // ROUND LOOP
            std::string color;
            std::stringstream ss2(round);
            while (validGame && std::getline(ss2, color, ',')) { // COLOR LOOP
                if ((color.find("red") != std::string::npos && std::stoi(color) > reference[RED]) ||
                (color.find("green") != std::string::npos && std::stoi(color) > reference[GREEN]) ||
                (color.find("blue") != std::string::npos && std::stoi(color) > reference[BLUE]))
                    validGame = false;
            }
        }
        if (validGame)
            total += game;
        game++;
    }
    std::cout << "Total: " << total << std::endl;
}