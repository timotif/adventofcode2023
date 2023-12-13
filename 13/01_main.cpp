#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::string> rotateGrid(std::vector<std::string> const &grid) {
    std::vector<std::string> ret;
    for (size_t j = 0; j < grid[0].size(); j++) {
        std::string line;
        for (size_t i = grid.size() - 1; i < grid.size(); i--) {
            line += grid[i][j];
        }
        ret.push_back(line);
    }
    return (ret);
}

std::ostream &operator<<(std::ostream &os, const std::vector<std::string> &grid) {
    for (size_t i = 0; i < grid.size(); i++) {
        os << grid[i] << std::endl;
    }
    return (os);
}

int findMirror(std::vector<std::string> const &grid) {
    int ret = 0;
    for (size_t i = 0; i < grid.size() - 1; i++) {
        // std::cout << "Checking " << i << std::endl;
        if (grid[i] == grid[i + 1]) { // Found candidate
            // std::cout << "Found candidate" << std::endl;
            bool valid = true;
            size_t curUp = i;
            size_t curDown = i + 1;
            while (1) {
                if (grid[curUp] != grid[curDown])
                    valid = false;
                if (curUp <= 0 || curDown >= grid.size() - 1)
                    break ;
                curUp--;
                curDown++;
            }
            ret += valid * (i + 1);
        }
    }
    return (ret);
}

int processGrid(std::vector<std::string> const &grid) {
    std::vector<std::string> rGrid = rotateGrid(grid);
    return (findMirror(grid) * 100 + findMirror(rGrid));
}

int main(void) {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return (1);
    }
    std::string line;
    std::vector<std::string> grid;
    uint64_t total = 0;
    while (std::getline(file, line)) {
        if (!line.empty())
            grid.push_back(line);
        else {
            total += processGrid(grid);
            grid.clear();
            continue ;
        }
    }
    file.close();
    std::cout << "Total: " << total + processGrid(grid) << std::endl;
}