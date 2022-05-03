#ifndef DISTRIBUTEDCOMPUTINGSYSTEM_MASTERCONFIG_H
#define DISTRIBUTEDCOMPUTINGSYSTEM_MASTERCONFIG_H


#include "Config.h"


namespace SCM {

    class MasterConfig: public config::ConfigInterface {

    public:

        std::string local_address = "127.0.0.1";  // your address

        std::string split_executable_path = "split.exe"; // path to split operation
        std::string compute_executable_path = "compute.exe"; // path to compute operation
        std::string merge_executable_path = "merge.exe"; // path to merge operation

        std::string input = "input";                    // file with keys description
        std::string worker_ips = "ips";                    // file with workers ips

        std::string query = "query";                    // file with query files generated after split
        std::string query_data = "query_data";                    // file with data files generated after split

        std::string key = "key";                    // file with query files generated after split
        std::string key_data = "key_data";                    // file with data files generated after split


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void load(std::string filename) override;
        void load(config::Config &config) override;

        void save(std::string filename) const override;
        void save(config::Config &config) const override;

    };

}


#endif //DISTRIBUTEDCOMPUTINGSYSTEM_MASTERCONFIG_H
