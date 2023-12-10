/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 21:00:25 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/10 21:00:26 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

enum e_map {
    SEED_TO_SOIL,
    SOIL_TO_FERT,
    FERT_TO_WATER,
    WATER_TO_LIGHT,
    LIGHT_TO_TEMP,
    TEMP_TO_HUMID,
    HUMID_TO_LOCATION,
};

enum e_data {
    DEST,
    SOURCE,
    RANGE,
    OFFSET,
};

typedef struct s_map {
    int   type;
    std::vector<int64_t>    data;
} t_map;

void printVec(std::vector<int64_t> v) {
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " "; 
    std::cout << std::endl;
}

void printRanges(std::vector<std::pair<int64_t, int64_t>> v) {
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i].first << " " << v[i].second << std::endl; 
    std::cout << std::endl;
}

int main(void) {
    std::ifstream file;
    file.open("input.txt");
    std::string line;
    std::vector<std::pair<int64_t, int64_t>> seeds;
    std::vector<t_map> maps;
    int type = -1;
    while (std::getline(file, line)) {
        if (line.compare(0, 7, "seeds: ") == 0) {   // SEEDS
            std::istringstream iss(line.substr(7));
            int64_t n1, n2;
            while (iss >> n1 >> n2) {
                seeds.push_back(std::make_pair(n1, n1 + n2));
            }
            // printRanges(seeds);
        }
        else if (line.empty()) {
            type++;
        }
        else if (std::isdigit(line[0])) {
            t_map map;
            map.type = type;
            for (size_t i = 0; i < line.length(); i++) {
                if (std::isdigit(line[i])) {
                    map.data.push_back(stol(line.substr(i)));
                while (std::isdigit(line[i]))
                    i++;    
                }
            }
            map.data.push_back(map.data[SOURCE] - map.data[DEST]);
            maps.push_back(map);
        }
    }
    file.close();
    type = SEED_TO_SOIL;
    size_t i = 0;
    while (i < maps.size()) { // BLOCK
        std::vector<t_map> ranges;
        while (maps[i].type == type && i < maps.size()) {
            ranges.push_back(maps[i]);
            i++;
        }
        std::vector<std::pair<int64_t, int64_t>> new_seeds;
        while (seeds.size() > 0) {
            std::pair<int64_t, int64_t> seed = seeds.back();
            seeds.pop_back();
            bool overlap;
            for (auto r : ranges) {
                overlap = false;
                int64_t os = std::max(seed.first, r.data[SOURCE]);
                int64_t oe = std::min(seed.second, r.data[SOURCE] + r.data[RANGE]);
                if (os < oe) {
                    overlap = true;
                    new_seeds.push_back(std::make_pair(
                        os - r.data[OFFSET],
                        oe - r.data[OFFSET]
                    ));
                    if (os > seed.first)
                        seeds.push_back(std::make_pair(seed.first, os));
                    if (oe < seed.second)
                        seeds.push_back(std::make_pair(oe, seed.second));
                    break ;
                }
            }
            if (!overlap) {
                new_seeds.push_back(seed);
            }
        }
        seeds = new_seeds;
        type++;
    }

    int64_t min = INT64_MAX;
    for (auto seed : seeds) {
        if (seed.first < min)
            min = seed.first;
    }
    std::cout << "Min: " << min << std::endl; 
}