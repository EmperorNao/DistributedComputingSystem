#include "ConnectionConfig.h"


void network::ConnectionConfig::load(std::string filename) {

    config::Config config;

    config.load(filename);
    load(config);

}


void network::ConnectionConfig::load(config::Config &config) {

    config.get_int("packet_size", packet_size);
    config.get("filename", filename);

    std::string str_type;
    config.get("type", str_type);

    if (str_type != "Server" and str_type != "Client") {
        throw std::domain_error(
                "Error in ConnectionConfig, "
                "type must be 'Client' or 'Server' "
                "but get '" + str_type + "'");
    }

    type = str_type == "Server" ? ManagerType::Server : ManagerType::Client;

    config.get_bool("threading", threading);
    config.get_bool("send_inf", send_inf);

    config.get("current_address", current_address);
    config.get("send_address", send_address);

    uint64_t val;
    config.get_uint("current_port", val);
    current_port = val;
    config.get_uint("send_port", val);
    send_port = val;

}


void network::ConnectionConfig::save(std::string filename) const {

    config::Config config;
    save(config);
    config.save(filename);

}


void network::ConnectionConfig::save(config::Config &config) const {

    config.set("packet_size", std::to_string(packet_size));
    config.set("filename", filename);

    config.set("type", type == ManagerType::Server ? "Server" : "Client");

    config.set("threading", threading ? "true" : "false");
    config.set("send_inf", send_inf ? "true" : "false");

    config.set("current_address", current_address);
    config.set("send_address", send_address);

    config.set("current_port", std::to_string(current_port));
    config.set("send_port", std::to_string(send_port));

}
