#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <string>
#include <map>

class ConfigReader {
private:
    std::map<std::string, std::string> values;
    void parseLine(const std::string& line);

public:
    ConfigReader(const std::string& configFile);
    float getFloatValue(const std::string& key);
    int getIntValue(const std::string& key);
};

#endif // CONFIGREADER_H
