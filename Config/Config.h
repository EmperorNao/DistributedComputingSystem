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
        bool exist(std::string key) { return this->content.contains(key); }
        void set(std::string key, std::string value) { this->content[key] = value; }

        [[nodiscard]] bool get_bool(std::string key) { return this->content[key] == "true"; }
        [[nodiscard]] int64_t get_int(std::string key) { return std::stoll(this->content[key]); }
        [[nodiscard]] uint64_t get_uint(std::string key) { return std::stoull(this->content[key]); }
        [[nodiscard]] double get_double(std::string key) { return std::stod(this->content[key]); }

        [[nodiscard]] std::string get(std::string key) { return this->content[key]; }
        void get_bool(std::string key, bool& val) { if (exist(key)) val = this->content[key] == "true"; }
        void get_int(std::string key, int64_t &val) { if (exist(key)) val = std::stoll(this->content[key]); }
        void get_uint(std::string key, uint64_t &val) { if (exist(key)) val = std::stoull(this->content[key]); }
        void get_double(std::string key, double &val) { if (exist(key)) val = std::stod(this->content[key]); }

        void get(std::string key, std::string &val) { if (exist(key)) val = this->content[key]; }

    };


    class ConfigInterface {

    public:
        virtual void load(std::string filename) = 0;
        virtual void load(config::Config& config) = 0;
        virtual void save(std::string filename) const = 0;
        virtual void save(config::Config& config) const = 0;

    };

}


#endif //DISTRIBUTEDCOMPUTINGSYSTEM_CONFIG_H
