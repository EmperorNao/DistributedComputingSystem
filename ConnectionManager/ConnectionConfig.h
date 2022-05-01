#ifndef DISTRIBUTEDCOMPUTINGSYSTEM_CONNECTIONCONFIG_H
#define DISTRIBUTEDCOMPUTINGSYSTEM_CONNECTIONCONFIG_H


#include "Config.h"


namespace network {


    enum class ManagerType {Server, Client};

class ConnectionConfig: public config::ConfigInterface {

    public:
        int64_t packet_size = 1024;                 // how many bytes contains in one packet
        std::string filename;                       // name of file to send or receive
        ManagerType type;                           // send or receive
        bool threading = false;                     // start run in this thread or create another one

        bool send_inf = false;                      // flag to server waiting infinite connections to which
        // send files

        int nums_to_send = 1;                       // how many times server needs to send files
        // doesn't work with send_inf set true

        std::string current_address = "127.0.0.1";  // your address
        unsigned short current_port = 27015;        // port in which open socket

        std::string send_address = "127.0.0.1";     // address of sender
        unsigned short send_port = 27015;           // port in which sender opened socket


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void load(std::string filename) override;
        void load(config::Config& config) override;
        void save(std::string filename) const override;
        void save(config::Config& config) const override;

    };


}


#endif //DISTRIBUTEDCOMPUTINGSYSTEM_CONNECTIONCONFIG_H
