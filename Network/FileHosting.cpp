#include "FileHosting.h"


void network::FileHosting::ping(std::string address) {

    manager.config.filename = message_name;
    manager.config.send_address = std::move(address);
    manager.config.type = network::ManagerType::Client;

    manager.run();

}


std::vector<std::string> network::FileHosting::get_files() {

    network::DataMessage msg;

    manager.config.type = network::ManagerType::Client;
    manager.config.filename = message_name;
    manager.run();

    msg.load(message_name);

    auto names = msg.get_files();
    for (auto& filename: names) {

        manager.config.filename = filename;
        manager.run();

    }

    return names;

}


void network::FileHosting::send_files(std::vector<std::string> files, std::string address) {

    network::DataMessage msg;

    msg.set_files(files);
    msg.save(message_name);

    manager.config.filename = message_name;
    manager.config.type = network::ManagerType::Server;
    manager.config.send_address = address;
    manager.run();

    for (auto& filename: files) {

        manager.config.filename = filename;
        manager.run();

    }

}


void network::FileHosting::waiting() {

    manager.config.type = network::ManagerType::Server;
    manager.config.filename = "tmp";
    manager.run();

}