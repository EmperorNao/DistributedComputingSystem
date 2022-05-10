#include <iostream>

#include "Master/Master.h"
#include "Worker/Worker.h"


int main(int argc, char** argv) {

    using namespace SCM;

    if (argc == 1 or std::string(argv[1]) == "--help") {
        std::cout << "Provide arguments:\n";
        std::cout << "--type [master/worker]\n";
        std::cout << "--config [config file name]\n";
        return 0;
    }

    int opt = -1;
    if (std::string(argv[1]) == "--type" and argc >= 3) {
        if (std::string(argv[2]) == "master")
            opt = 1;
        if (std::string(argv[2]) == "worker")
            opt = 0;
    }

    if (opt == -1) {
        std::cout << "Provide right application type [master/worker]\n";
        return 0;
    }

    std::string filename;
    if (argc >= 5 and std::string(argv[3]) == "--config") {
        filename = std::string(argv[4]);
    }

    if (opt) {

        MasterConfig masterConfig;
        masterConfig.load(filename);

        Master m(masterConfig);
        m.run();

    }
    else {

        WorkerConfig workerConfig;
        workerConfig.load(filename);

        Worker w(workerConfig);
        w.run();

    }

}
