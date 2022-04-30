#ifndef DISTRIBUTEDCOMPUTINGSYSTEM_CONNECTIONMANAGER_H
#define DISTRIBUTEDCOMPUTINGSYSTEM_CONNECTIONMANAGER_H


#include "ISendable.h"
#include "Socket.h"


#include <memory>
#include <thread>
#include <utility>
#include <limits>


namespace network {

    enum class ManagerType {Server, Client};

    struct connection_configuration {

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

    };


    class ConnectionManager {

    private:

        connection_configuration config;

        static std::string err() {

            return std::to_string(WSAGetLastError());

        }

        // In case if config.threading is true, inner functions will be called in separate thread
        // same for receive and listening

        void receive();
        static void inner_receive(connection_configuration config);

        void listening_and_sending();
        static void inner_listening_and_sending(connection_configuration config);

        static void send_with_socket(std::string filename, std::shared_ptr<Socket> s, int64_t packet_size);

    public:
        explicit ConnectionManager(connection_configuration conf): config(std::move(conf)) {
            WSADATA data;
            if (WSAStartup(MAKEWORD(2, 2), &data) != NO_ERROR) {
                throw std::domain_error("Error in WSAStartup");
            }
        };
        ~ConnectionManager() {
            WSACleanup();
        }

        [[nodiscard]] connection_configuration get_config() const { return config; };
        void set_config(const connection_configuration& conf) { config = conf; }

        void run() {

            if (this->config.type == ManagerType::Server) {
                this->listening_and_sending();
            }
            if (this->config.type == ManagerType::Client) {
                this->receive();
            }

        }

    };

}


#endif //DISTRIBUTEDCOMPUTINGSYSTEM_CONNECTIONMANAGER_H
