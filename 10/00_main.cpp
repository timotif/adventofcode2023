#include <fstream>
#include <iostream>
#include <vector>
#include <deque>
#include <set>
#define UP "S|F7"
#define DOWN "S|LJ"
#define LEFT "S-LF"
#define RIGHT "S-J7"

void printGrid(std::vector<std::string> grid) {
    for (auto line : grid) {
        std::cout << line << std::endl;
    }
    std::cout << std::endl;
}

bool canGo(char c, std::string s) {
    for (auto ch : s)
        if (c == ch) return true;
    return (false);
}

bool connectsTo(char c, std::string s) {
    for (auto ch : s)
        if (c == ch) return true;
    return (false);
}

int main(void) {
    std::ifstream file("input.txt");
    std::vector<std::string> grid;
    std::string line;
    while (std::getline(file, line)) {
        grid.push_back(line);
    }
    std::deque<std::pair<int, int>> path;
    std::set<std::pair<int, int>> visited;
    // Find starting point
    bool foundS = false;
    for (size_t i = 0; i < grid.size(); i++) {
        if (foundS) break ;
        for (size_t j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'S') {
                std::cout << "Found starting point at (" << j << ", " << i << ")" << std::endl;
                path.push_back(std::make_pair(i, j));
                foundS = true;
                break ;
            }
        }
    }
    // Checking movements
    int steps = 0;
    for (size_t i = 0; i < path.size(); i++){
        uint32_t row = path[i].first;
        uint32_t col = path[i].second;
        if (col > 0 && connectsTo(grid[row][col], RIGHT) && canGo(grid[row][col - 1], LEFT) && visited.count(std::make_pair(row, col - 1)) == 0) {
            path.push_back(std::make_pair(row, col - 1));
            visited.insert(path[i]);
            steps++;
        }
        if (col < grid[0].length() - 1 && connectsTo(grid[row][col], LEFT) && canGo(grid[row][col + 1], RIGHT) && visited.count(std::make_pair(row, col + 1)) == 0) {
            path.push_back(std::make_pair(row, col + 1));
            visited.insert(path[i]);
            steps++;
        }
        if (row > 0 && connectsTo(grid[row][col], DOWN) && canGo(grid[row - 1][col], UP) && visited.count(std::make_pair(row - 1, col)) == 0) {
            path.push_back(std::make_pair(row - 1, col));
            visited.insert(path[i]);
            steps++;
        }
        if (row < grid.size() - 1 && connectsTo(grid[row][col], UP) && canGo(grid[row + 1][col], DOWN) && visited.count(std::make_pair(row + 1, col)) == 0) {
            path.push_back(std::make_pair(row + 1, col));
            visited.insert(path[i]);
            steps++;
        }
    }
    std::cout << "Steps: " << (visited.size() + 1) / 2 << std::endl;
}