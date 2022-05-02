#include "MasterConfig.h"


void SCM::MasterConfig::load(std::string filename) {

    config::Config config;

    config.load(filename);
    load(config);

}


void SCM::MasterConfig::load(config::Config &config) {

    config.get("local_address", local_address);

    config.get("split_executable_path", split_executable_path);
    config.get("merge_executable_path", merge_executable_path);

    config.get("input", input);
    config.get("worker_ips", worker_ips);

}


void SCM::MasterConfig::save(std::string filename) const {

    config::Config config;
    save(config);
    config.save(filename);

}


void SCM::MasterConfig::save(config::Config &config) const {

    config.set("local_address", local_address);

    config.set("split_executable_path", split_executable_path);
    config.set("merge_executable_path", merge_executable_path);

    config.set("input", input);
    config.set("worker_ips", worker_ips);

}
