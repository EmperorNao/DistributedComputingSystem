#include "Config.h"


void config::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}


void config::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}


void config::trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}


void config::Config::load(std::string filename, std::string delimiter) {

    if (not filename.ends_with(".conf")) {
        throw std::domain_error("Config file should have extension .conf");
    }

    std::ifstream file(filename);
    std::string line;

    int number_of_line = 0;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        number_of_line += 1;

        uint64_t pos = line.find(delimiter);
        if (pos == std::string::npos) {
            throw std::domain_error(
                    "Config file " + filename +
                    " don't match for delimiter '" + delimiter +
                    "' in line " + std::to_string(number_of_line)
                    );
        }

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1, line.size() - pos - 1);
        trim(key);
        trim(value);

        this->content[key] = value;

    }

}


void config::Config::save(std::string filename, std::string delimiter, bool append) const {

    if (not filename.ends_with(".conf")) {
        throw std::domain_error("Config file should have extension .conf");
    }

    std::ofstream file;
    if (append) {
        file.open(filename, std::ios::app);
    }
    else {
        file.open(filename);
    }

    for (auto& pair: content) {
        file << pair.first << delimiter << pair.second << std::endl;
    }

}
