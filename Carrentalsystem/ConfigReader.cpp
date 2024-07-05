#include "ConfigReader.h"
#include <fstream>
#include <sstream>

ConfigReader::ConfigReader(const std::string& configFile) {
    std::ifstream file(configFile);
    std::string line;
    while (getline(file, line)) {
        parseLine(line);
    }
    file.close();
}

void ConfigReader::parseLine(const std::string& line) {
    if (line.empty() || line[0] == '#') return; // Skip comments and empty lines

    std::istringstream iss(line);
    std::string key, value;
    if (getline(iss, key, '=') && getline(iss, value)) {
        values[key] = value;
    }
}

float ConfigReader::getFloatValue(const std::string& key) {
    return std::stof(values.at(key));
}

int ConfigReader::getIntValue(const std::string& key) {
    return std::stoi(values.at(key));
}
