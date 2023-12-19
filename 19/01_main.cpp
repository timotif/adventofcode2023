/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:46:48 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/19 10:46:49 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>

typedef struct s_part {
    std::map<char, std::pair<int, int>> features;
    bool accepted;
} t_part;

void printPart(std::map<char, std::pair<int, int>> p) {
    std::cout << "{";
    for (auto pair : p) {
        std::cout << "'" << pair.first << "': (" << pair.second.first << ", " << pair.second.second << ")" << (pair.first == 's' ? "" : ", ");
    }
}

uint64_t count(std::map<std::string, std::list<std::string>> workflows, std::map<char, std::pair<int, int>> ranges, std::string wfName = "in") {
    if (wfName == "R")
        return (0);
    if (wfName == "A") {
        uint64_t prod = 1;
        for (auto pair : ranges) {
            prod *= pair.second.second - pair.second.first + 1;
        }
        return (prod);
    }
    uint64_t tot = 0;
    bool through = true;
    for (auto wf : workflows[wfName]) {
        if (wf.find(':') != std::string::npos) {
            char key = wf[0];
            char comp = wf[1];
            int val = std::stoi(wf.substr(2));
            std::string fallback = wf.substr(wf.find(':') + 1);
            int lo = ranges[key].first;
            int hi = ranges[key].second;
            std::pair<int, int> t, f;
            if (comp == '<') {
                t = std::make_pair(lo, val - 1);
                f = std::make_pair(val, hi);
            } else {
                t = std::make_pair(val + 1, hi);
                f = std::make_pair(lo, val);
            }
            if (t.first <= t.second) {
                std::map<char, std::pair<int, int>> tmp;
                tmp = ranges;
                tmp[key] = t;
                tot += count(workflows, tmp, fallback);
            }
            if (f.first <= f.second) {
                ranges = ranges;
                ranges[key] = f;
            }
            else {
                through = false;
                break ;
            }
        }
    }
    if (through)
        tot += count(workflows, ranges, workflows[wfName].back());
    return (tot);
}

int main(void) {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return 1;
    }
    std::map<std::string, std::list<std::string>> workflows;
    std::string line;
    // Workflows
    while (std::getline(file, line)) {
        if (line.empty())
            break;
        std::string name = line.substr(0, line.find('{'));
        line = line.substr(line.find('{') + 1);
        line = line.substr(0, line.find('}'));
        std::stringstream ss(line);
        while (std::getline(ss, line, ','))
            workflows[name].push_back(line);
    }
    std::cout << count(workflows, {{'x', {1, 4000}}, {'m', {1, 4000}}, {'a', {1, 4000}}, {'s', {1, 4000}}}) << std::endl;
}