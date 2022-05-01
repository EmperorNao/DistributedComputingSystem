#include "WorkerConfig.h"


void SCM::WorkerConfig::load(std::string filename) {

    config::Config config;

    config.load(filename);
    load(config);

}


void SCM::WorkerConfig::load(config::Config &config) {

    config.get("local_address", local_address);
    config.get("server_address", server_address);
    config.get("compute_executable_path", compute_executable_path);

}


void SCM::WorkerConfig::save(std::string filename) const {

    config::Config config;
    save(config);
    config.save(filename);

}


void SCM::WorkerConfig::save(config::Config &config) const {

    config.set("local_address", local_address);
    config.set("server_address", server_address);
    config.set("compute_executable_path", compute_executable_path);

}
