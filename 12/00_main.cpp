#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>

std::ostream &operator<<(std::ostream &out, std::vector<int> vec) {
    out << "(";
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
        out << *it << (it + 1 == vec.end() ? "" : ", ");
    }
    out << ")";
    return (out);
}

void printVecInt(std::vector<int> vec) {
    std::cout << "[";
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
        std::cout << *it << (it + 1 == vec.end() ? "" : ", ");
    }
    std::cout << "]";
}

std::vector<int> parseMap(std::string map) {
    std::vector<int> ret;
    for (std::string::iterator it = map.begin(); it != map.end(); it++) {
        int c = 0;
        if (*it == '#' && (it == map.begin() || *(it - 1) != '#')) {
            c++;
            while (*(it + 1) == '#') {
                c++;
                it++;
            }
            ret.push_back(c);
        }
    }
    return (ret);
}

std::vector<int> parseNums(std::string nums) {
    std::vector<int> ret;
    std::stringstream ss(nums);
    while (getline(ss, nums, ',')) {
        ret.push_back(std::stoi(nums));
    }
    return (ret);
}

bool mapFilled(std::string map) {
    for (size_t i = 0; i < map.size(); i++) {
        if (map[i] == '?')
            return (false);
    }
    return (true);
}

int compute(std::string map, std::vector<int> nums, size_t i) {
    if (i == map.size()) {
        return (parseMap(map) == nums);
    }
    if (map[i] == '?') {
        int ret = 0;
        ret += compute(map.substr(0, i) + '#' + map.substr(i + 1), nums, i + 1);
        ret += compute(map.substr(0, i) + '.' + map.substr(i + 1), nums, i + 1);
        return (ret);
    }
    else
        return (compute(map, nums, i + 1));
}

int main(void) {
    std::ifstream file("input.txt");
    std::string line;
    int ret = 0;
    while (std::getline(file, line)) {
        size_t pos = line.find(' ');
        std::vector<int> map = parseMap(line.substr(0, pos));
        std::vector<int> nums = parseNums(line.substr(pos + 1));
        int solutions = compute(line.substr(0, pos), nums, 0);
        ret += solutions;
        std::cout << line.substr(0, pos) << " " << nums << " " << solutions << std::endl;
    }
    std::cout << ret << std::endl;
}