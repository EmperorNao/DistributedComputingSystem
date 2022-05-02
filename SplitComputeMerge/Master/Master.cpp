#include "Master.h"


void SCM::Master::run() {

    auto ips = scheme::extract_lines(config.worker_ips);
    auto input = scheme::extract_lines(config.input);

    // splitting
    scheme::call(config.split_executable_path, scheme::construct_eval_string(input) + " " + std::to_string(ips.size()));

    // configuring
    std::string message_name = "message.msg";
    network::ConnectionConfig inet_config;
    network::ConnectionManager manager(inet_config);
    inet_config.type = network::ManagerType::Client;
    network::DataMessage msg;

    // sending ping for all ips
    for (auto& ip: ips) {
        inet_config.send_address = ip;
        inet_config.threading = true;
        manager.set_config(inet_config);
        manager.run();
    }







    // do splitting
    // thread per each

        // ping
        // send query
        // send data
        // waiting
        // get data back
        // increase counter of how much is ok

    // sleep while not get all cont ? or maybe mutex lock

    // merging

    // OK

}
