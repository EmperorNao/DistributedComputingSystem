#ifndef DISTRIBUTEDCOMPUTINGSYSTEM_MASTER_H
#define DISTRIBUTEDCOMPUTINGSYSTEM_MASTER_H


#include "MasterConfig.h"
#include "ConnectionManager.h"
#include "ControlMessage.h"
#include "FileHosting.h"
#include "Distributable.h"
#include "exec.h"

#include <thread>
#include <atomic>


namespace SCM {

class Master: public network::FileHosting {

    private:

        volatile std::atomic_int64_t number_threads_ended; // counter for ended threads

        MasterConfig config;
        void split(SCM::FileData input, uint64_t n_jobs) const;
        void merge(std::vector<std::string> keys, std::vector<std::string> datas) const;

        static void worker_interaction(std::string address,
                                       std::string query_file,
                                       std::string data_file,
                                       const MasterConfig& config,
                                       volatile std::atomic_int64_t& number_threads_ended);

        void start_interactions(const std::vector<std::string>& workers_ips,
                                const std::vector<std::string>& query_files,
                                const std::vector<std::string>& data_files);

    public:
        explicit Master(const MasterConfig &conf) : config(conf) {};
        void run();


    };

}


#endif //DISTRIBUTEDCOMPUTINGSYSTEM_MASTER_H
