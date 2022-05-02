#ifndef DISTRIBUTEDCOMPUTINGSYSTEM_WORKER_H
#define DISTRIBUTEDCOMPUTINGSYSTEM_WORKER_H


#include "WorkerConfig.h"
#include "ConnectionManager.h"
#include "ControlMessage.h"
#include "Distributable.h"
#include "exec.h"

#include <utility>


namespace SCM {

    class Worker {

    private:
        WorkerConfig config;
        const std::string message_name = "message.msg";
        network::ConnectionConfig inet_config;
        network::ConnectionManager manager;


        void waiting_master();
        void ping(std::string address);

        void get_compute_executable();
        SCM::FileData SCM::Worker::get_files();
        void send_files(SCM::FileData);

        void compute(SCM::Query query, SCM::FileData data);


    public:
        explicit Worker(const WorkerConfig& conf): config(conf), manager(inet_config) {};
        void run();

    };


}


#endif //DISTRIBUTEDCOMPUTINGSYSTEM_WORKER_H
