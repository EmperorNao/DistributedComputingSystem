#ifndef DISTRIBUTEDCOMPUTINGSYSTEM_CONNECTIONMANAGER_H
#define DISTRIBUTEDCOMPUTINGSYSTEM_CONNECTIONMANAGER_H


#include <memory>
#include <thread>
#include <utility>
#include <limits>
#include <chrono>


#include "ISendable.h"
#include "Socket.h"
#include "ConnectionConfig.h"


namespace network {

    class ConnectionManager {

    private:

        ConnectionConfig config;

        static std::string err() {

            return std::to_string(WSAGetLastError());

        }

        // In case if config.threading is true, inner functions will be called in separate thread
        // same for receive and listening

        void receive();
        static void inner_receive(ConnectionConfig config);

        void listening_and_sending();
        static void inner_listening_and_sending(ConnectionConfig config);

        static void send_with_socket(std::string filename, std::shared_ptr<Socket> s, int64_t packet_size);

    public:
        explicit ConnectionManager(const ConnectionConfig& conf): config(conf) {
            WSADATA data;
            if (WSAStartup(MAKEWORD(2, 2), &data) != NO_ERROR) {
                throw std::domain_error("Error in WSAStartup");
            }
        };
        ~ConnectionManager() {
            WSACleanup();
        }

        [[nodiscard]] ConnectionConfig get_config() const { return config; };
        void set_config(const ConnectionConfig& conf) { config = conf; }

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
