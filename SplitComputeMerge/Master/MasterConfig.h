#ifndef DISTRIBUTEDCOMPUTINGSYSTEM_MASTERCONFIG_H
#define DISTRIBUTEDCOMPUTINGSYSTEM_MASTERCONFIG_H


#include "Config.h"


namespace SCM {

    class MasterConfig: public config::ConfigInterface {

    public:

        std::string local_address = "127.0.0.1";  // your address

        std::string split_executable_path = "compute"; // path to compute operation
        std::string merge_executable_path = "merge"; // path to merge operation

        std::string input = "input";                    // file with keys description
        std::string worker_ips = "ips";                    // file with workers ips

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void load(std::string filename) override;
        void load(config::Config &config) override;

        void save(std::string filename) const override;
        void save(config::Config &config) const override;

    };

}


#endif //DISTRIBUTEDCOMPUTINGSYSTEM_MASTERCONFIG_H
