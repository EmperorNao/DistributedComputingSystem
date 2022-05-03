#ifndef DISTRIBUTEDCOMPUTINGSYSTEM_WORKERCONFIG_H
#define DISTRIBUTEDCOMPUTINGSYSTEM_WORKERCONFIG_H


#include "Config.h"


namespace SCM {

    class WorkerConfig: public config::ConfigInterface {

    public:

        std::string local_address = "127.0.0.1";  // your address
        std::string master_address = "127.0.0.1";   // address of master
        std::string compute_executable_name = "compute.exe"; // compute name

        std::string key = "key";                    // file with keys description
        std::string data = "data";                    // file with datas description

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void load(std::string filename) override;
        void load(config::Config &config) override;

        void save(std::string filename) const override;
        void save(config::Config &config) const override;

    };

}


#endif //DISTRIBUTEDCOMPUTINGSYSTEM_WORKERCONFIG_H
