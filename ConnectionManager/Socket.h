#ifndef DISTRIBUTEDCOMPUTINGSYSTEM_SOCKET_H
#define DISTRIBUTEDCOMPUTINGSYSTEM_SOCKET_H


#include <iostream>
#include <string>
#include <winsock2.h>


namespace network {

    class Socket {

    private:
        SOCKET socket_descriptor = INVALID_SOCKET;

    public:

        explicit Socket(SOCKET s) : socket_descriptor(s) {};

        Socket(const std::string& address, unsigned short port, bool listening = false);


        [[nodiscard]] bool is_valid() const {
            return socket_descriptor != INVALID_SOCKET;
        }

        [[nodiscard]] SOCKET get_descriptor() const {
            return socket_descriptor;
        }

        ~Socket() {
            closesocket(socket_descriptor);
        }

    };

}

#endif //DISTRIBUTEDCOMPUTINGSYSTEM_SOCKET_H
