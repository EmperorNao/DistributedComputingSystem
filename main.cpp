#include <iostream>
#include "ConnectionManager.h"
#include "Config.h"
#include "exec.h"


#include "Master/Master.h"
#include "Worker/Worker.h"


int main() {

//    std::cout << "Option\n";
//
//
////    config::Config config;
////
////    config.set("threading", "true");
////    config.save("Test.conf");
////
////    config.refresh();
////
////    config.load("Test.conf");
////    bool val = false;
////    config.get_bool("threading", val);
//    network::ConnectionConfig conf;
//    network::ConnectionManager manager(conf);
//
//    int option;
//    std::cout << "Input option: Client/Master (0/1)\n";
//    std::cin >> option;
//
//    conf.filename = "test.txt";
//    if (option) {
//        conf.type = network::ManagerType::Server;
//        conf.send_inf = true;
//    } else {
//        conf.type = network::ManagerType::Client;
//        //conf.load("Connection.conf");
//    }
//
//    //conf.save("Connection.conf");
//
//    manager.set_config(conf);
//    manager.run();
//    std::cin.get();
//    std::cin.get();
//
//    return 0;

    using namespace SCM;


    int opt;
    std::cout << "Input Options Master/Worker (1/0)\n";
    std::cin >> opt;

    if (opt) {

        MasterConfig masterConfig;
        masterConfig.load("MasterConfig.conf");
        Master m(masterConfig);
        m.run();
        std::cin.get();
        std::cin.get();
        std::cin.get();


    }
    else {

        WorkerConfig workerConfig;
        Worker w(workerConfig);
        w.run();
        std::cin.get();
        std::cin.get();
        std::cin.get();


    }

}
