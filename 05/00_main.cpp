#include <fstream>
#include <iostream>
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

int main(void) {
    std::ifstream file;
    file.open("input.txt");
    std::string line;
    std::vector<int64_t> seeds;
    std::vector<t_map> maps;
    int type = -1;
    // int counter = 0;
    while (std::getline(file, line)) {
        if (line.compare(0, 7, "seeds: ") == 0) {   // SEEDS
            for (size_t i = 0; i < line.length(); i++) {
                if (std::isdigit(line[i])) {
                    seeds.push_back(stol(line.substr(i)));
                while (std::isdigit(line[i]))
                    i++;    
                }
            }
            // printVec(seeds);
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
            // std::cout << "Map: " << map.type << " - ";
            // printVec(map.data);
        }
    }
    // std::cout << "Total maps: " << maps.size() << std::endl;
    file.close();
    int64_t min = INT64_MAX;
    for (auto seed : seeds) {
        // std::cout << "*************\nSeed: " << seed << std::endl;
        for (size_t i = 0; i < maps.size(); i++) {
            t_map map = maps[i];
            // std::cout << "Checking Map: " << map.type << " - " << seed << " Type: " << type << std::endl;
            if (map.data[SOURCE] <= seed && seed < map.data[SOURCE] + map.data[RANGE]) {
                seed = seed - map.data[OFFSET];
                // std::cout << "Map: " << map.type << " - " << seed << std::endl;
                int type = map.type; 
                while (i < maps.size() - 1 && type == maps[i + 1].type) {
                    i++;
                    // std::cout << "Skipping to " << maps[i].type << std::endl;
                }
            }
        }
        if (seed < min)
            min = seed; 
    }
    std::cout << "Min: " << min << std::endl;    
}