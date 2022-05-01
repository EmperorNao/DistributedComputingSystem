#ifndef DISTRIBUTEDCOMPUTINGSYSTEM_WORKERCONFIG_H
#define DISTRIBUTEDCOMPUTINGSYSTEM_WORKERCONFIG_H


#include "Config.h"


namespace SCM {

    class WorkerConfig: public config::ConfigInterface {

    public:

        std::string local_address = "127.0.0.1";  // your address
        std::string server_address = "127.0.0.1";   // address of server
        std::string compute_executable_path = "compute";

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void load(std::string filename) override;
        void load(config::Config &config) override;

        void save(std::string filename) const override;
        void save(config::Config &config) const override;

    };

}


#endif //DISTRIBUTEDCOMPUTINGSYSTEM_WORKERCONFIG_H
