#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>

typedef struct s_part {
    std::map<char, int> features;
    bool accepted;
} t_part;

bool parseWorkflow(std::map<std::string, std::list<std::string>> &workflows, t_part p, std::string wfName = "in") {
    if (wfName == "R")
        return (false);
    if (wfName == "A")
        return (true);
    std::list<std::string>::iterator it = workflows[wfName].begin();
    while (it != workflows[wfName].end()) {
        if ((*it).find(':') != std::string::npos) {
            char key = (*it)[0];
            char comp = (*it)[1];
            int val = std::stoi((*it).substr(2));
            std::string fallback = (*it).substr((*it).find(':') + 1);
            if ((comp == '<' && p.features[key] < val) || (comp == '>' && p.features[key] > val)) {
                    return (parseWorkflow(workflows, p, fallback));
            }
        }
        it++;
    }
    return (parseWorkflow(workflows, p, workflows[wfName].back()));
}

int sumFeatures(t_part p) {
    int sum = 0;
    for (auto pair : p.features)
        sum += pair.second;
    return (sum);
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
        // std::cout << line << std::endl;
        std::stringstream ss(line);
        while (std::getline(ss, line, ','))
            workflows[name].push_back(line);
    }
    // Parts
    std::list<t_part> parts;
    while (std::getline(file, line)) {
        line = line.substr(line.find('{') + 1);
        line = line.substr(0, line.find('}'));
        t_part p;
        for (int i = 0; i < 4; i++) {
            char key = line[0];
            p.features[key] = std::stoi(line.substr(line.find('=') + 1));
            line = line.substr(line.find(',') + 1);
        }
        parts.push_back(p);
    }
    int total = 0;
    for (auto p : parts) {
        if (parseWorkflow(workflows, p))
            total += sumFeatures(p);
    }
    std::cout << total << std::endl;
}