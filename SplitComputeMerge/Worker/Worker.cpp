#include "Worker.h"


void SCM::Worker::run() {

    // waiting for getting ping by master
    waiting();

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

    send_files(key, config.master_address);
    send_files(data_output, config.master_address);
    std::cout << "Worker finished\n";

}


void SCM::Worker::get_compute_executable() {

    manager.config.filename = config.compute_executable_name;
    manager.config.type = network::ManagerType::Client;
    manager.config.send_address = config.master_address;

    manager.run();

}


void SCM::Worker::compute(SCM::Query query, SCM::FileData data) {

    scheme::call(config.compute_executable_name,
                 scheme::construct_eval_string(query) + " " + scheme::construct_eval_string(data));

}
