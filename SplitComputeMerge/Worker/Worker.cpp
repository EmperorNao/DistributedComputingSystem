#include "Worker.h"


void SCM::Worker::run() {

    // waiting for getting ping by master
    waiting_master();

    // get compute_program
    get_compute_executable();

    // get inputs
    SCM::Query query = get_files();
    SCM::FileData data_input = get_files();

    // start compute
    compute(query, data_input);

    // get outputs
    SCM::Key key = scheme::extract_lines(config.key);
    SCM::FileData data_output = scheme::extract_lines(config.data);

    // send results back
    ping(config.master_address);

    send_files(key);
    send_files(data_output);


}


void SCM::Worker::waiting_master() {

    manager.config.type = network::ManagerType::Server;
    manager.config.filename = "tmp";

    manager.run();

}


SCM::FileData SCM::Worker::get_files() {

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


void SCM::Worker::send_files(SCM::FileData files) {

    network::DataMessage msg;

    msg.set_files(files);
    msg.save(message_name);

    manager.config.filename = message_name;
    manager.config.type = network::ManagerType::Server;
    manager.config.send_address = config.master_address;
    manager.run();

    for (auto& filename: files) {

        manager.config.filename = filename;
        manager.run();

    }

}


void SCM::Worker::get_compute_executable() {

    manager.config.filename = config.compute_executable_name;
    manager.config.type = network::ManagerType::Client;
    manager.config.send_address = config.master_address;

    manager.run();

}


void SCM::Worker::ping(std::string address) {

    manager.config.filename = config.compute_executable_name;
    manager.config.send_address = std::move(address);
    manager.config.type = network::ManagerType::Client;

    manager.run();


}


void SCM::Worker::compute(SCM::Query query, SCM::FileData data) {

    scheme::call(config.compute_executable_name,
                 scheme::construct_eval_string(query) + " " + scheme::construct_eval_string(data));

}
