#ifndef DISTRIBUTEDCOMPUTINGSYSTEM_FILEHOSTING_H
#define DISTRIBUTEDCOMPUTINGSYSTEM_FILEHOSTING_H


#include "ConnectionManager.h"
#include "ControlMessage.h"

#include <iostream>
#include <vector>
#include <string>


namespace network {

    const static std::string message_name = "message.msg";

    class FileHosting {

    protected:

        network::ConnectionConfig inet_config;
        network::ConnectionManager manager;

        virtual void waiting() final;
        virtual void ping(std::string address) final;
        virtual std::vector<std::string> get_files(std::string msg_name = "message.msg") final;
        virtual void send_files(std::vector<std::string> files, std::string address) final;

    public:

        explicit FileHosting(): manager(inet_config) {

        }

    };

}


#endif //DISTRIBUTEDCOMPUTINGSYSTEM_FILEHOSTING_H
