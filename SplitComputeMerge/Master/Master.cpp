#include "Master.h"


void SCM::Master::run() {

    auto workers_ip = scheme::extract_lines(config.worker_ips);
    auto input = scheme::extract_lines(config.input);

    int64_t number_of_workers = workers_ip.size();
    // splitting
    split(input, workers_ip.size());

    // getting files of files
    auto query_files = scheme::extract_lines(config.query);
    auto query_data_files = scheme::extract_lines(config.query_data);

    // start threading and interactions with workers
    start_interactions(workers_ip, query_files, query_data_files);

    while (number_threads_ended != number_of_workers);

    auto key_files = scheme::extract_lines(config.query);
    auto key_data_files = scheme::extract_lines(config.key_data);

    // merge
    merge(key_files, key_data_files);

    std::cin.get();

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


void SCM::Master::split(SCM::FileData input, uint64_t n_jobs) const {

    scheme::call(config.split_executable_path, scheme::construct_eval_string(input) + " " + std::to_string(n_jobs));

}



void SCM::Master::worker_interaction(std::string address, std::string query_file, std::string data_file,
                                     const SCM::MasterConfig &config, volatile std::atomic_int64_t& number_threads_ended) {

    network::ConnectionConfig inet_config;
    network::ConnectionManager manager(inet_config);
    network::DataMessage msg;
    std::vector<std::string> files;



    manager.config.filename = network::message_name;
    manager.config.send_address = std::move(address);
    manager.config.type = network::ManagerType::Client;

    manager.run();



    files = scheme::extract_lines(query_file);
    msg.set_files(files);
    msg.save(network::message_name);

    manager.config.filename = network::message_name;
    manager.config.type = network::ManagerType::Server;
    manager.config.send_address = address;
    manager.run();

    for (auto& filename: files) {

        manager.config.filename = filename;
        manager.run();

    }


    files = scheme::extract_lines(data_file);
    msg.set_files(files);
    msg.save(network::message_name);

    manager.config.filename = network::message_name;
    manager.config.type = network::ManagerType::Server;
    manager.config.send_address = address;
    manager.run();

    for (auto& filename: files) {

        manager.config.filename = filename;
        manager.run();

    }



    manager.config.type = network::ManagerType::Server;
    manager.config.filename = "tmp";
    manager.run();


    auto key_names = scheme::extract_lines(config.key);
    auto key_data_names = scheme::extract_lines(config.key_data);


    manager.config.type = network::ManagerType::Client;
    manager.config.filename = address + "_key";
    manager.run();

    msg.load(address + "_key");

    files = msg.get_files();
    for (auto& filename: files) {

        manager.config.filename = filename;
        manager.run();

    }


    manager.config.type = network::ManagerType::Client;
    manager.config.filename = address + "_keydata";
    manager.run();

    msg.load(address + "_keydata");

    files = msg.get_files();
    for (auto& filename: files) {

        manager.config.filename = filename;
        manager.run();
    }

    number_threads_ended += 1;

}


void SCM::Master::start_interactions(const std::vector<std::string>& workers_ips,
                                     const std::vector<std::string>& query_files,
                                     const std::vector<std::string>& data_files) {

    number_threads_ended = 0;
    int64_t n = workers_ips.size();
    for (int64_t i = 0; i < n; ++i ) {
        std::thread t(worker_interaction, workers_ips[i], query_files[i], data_files[i], std::ref(config),
                      std::ref(number_threads_ended));
    }

}


void SCM::Master::merge(std::vector<std::string> keys, std::vector<std::string> data) const {

    std::string args;
    std::vector<std::string> files;

    args += keys.size();
    args += " ";

    for (int64_t i = 0; i < keys.size(); ++i) {

        files = scheme::extract_lines(keys[i]);
        args += scheme::construct_eval_string(files);
        args += " ";

        files = scheme::extract_lines(data[i]);
        args += scheme::construct_eval_string(files);
        args += " ";

    }

    scheme::call(config.merge_executable_path, args);

}
