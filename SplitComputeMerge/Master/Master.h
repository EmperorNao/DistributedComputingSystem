#ifndef DISTRIBUTEDCOMPUTINGSYSTEM_MASTER_H
#define DISTRIBUTEDCOMPUTINGSYSTEM_MASTER_H


#include "MasterConfig.h"
#include "ConnectionManager.h"
#include "ControlMessage.h"
#include "Distributable.h"
#include "exec.h"


namespace SCM {

    class Master {

    private:
        MasterConfig config;
        void send_datas();

    public:
        explicit Master(const MasterConfig &conf) : config(conf) {};
        void run();


    };

}


#endif //DISTRIBUTEDCOMPUTINGSYSTEM_MASTER_H
