#include "WorkerConfig.h"


void SCM::WorkerConfig::load(std::string filename) {

    config::Config config;

    config.load(filename);
    load(config);

}


void SCM::WorkerConfig::load(config::Config &config) {

    config.get("local_address", local_address);
    config.get("master_address", master_address);

    config.get("compute_executable_path", compute_executable_path);

    config.get("key", key);
    config.get("data", data);

}


void SCM::WorkerConfig::save(std::string filename) const {

    config::Config config;
    save(config);
    config.save(filename);

}


void SCM::WorkerConfig::save(config::Config &config) const {

    config.set("local_address", local_address);
    config.set("master_address", master_address);

    config.set("compute_executable_path", compute_executable_path);

    config.set("key", key);
    config.set("data", data);

}
