#ifndef DISTRIBUTEDCOMPUTINGSYSTEM_CONFIG_H
#define DISTRIBUTEDCOMPUTINGSYSTEM_CONFIG_H


#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include <map>


namespace config {


    static inline void ltrim(std::string &s);
    static inline void rtrim(std::string &s);
    static inline void trim(std::string &s);


    class Config {

    private:
        std::map<std::string, std::string> content;

    public:

        void load(std::string filename, std::string delimiter = "=");
        void save(std::string filename, std::string delimiter = " = ", bool append = false) const;
        void refresh() { this->content.clear(); }


        bool get_bool(std::string key) { return this->content[key] == "true"; }
        int64_t get_int(std::string key) { return std::stoll(this->content[key]); }
        uint64_t get_uint(std::string key) { return std::stoull(this->content[key]); }
        double get_double(std::string key) { return std::stod(this->content[key]); }
        std::string get(std::string key) { return this->content[key]; }

        void set(std::string key, std::string value) { this->content[key] = value; }


    };

}


#endif //DISTRIBUTEDCOMPUTINGSYSTEM_CONFIG_H
