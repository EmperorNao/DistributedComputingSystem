#include "Socket.h"


network::Socket::Socket(const std::string &address, unsigned short port, bool listening) {

    socket_descriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (socket_descriptor == INVALID_SOCKET) {
        throw std::domain_error("Error in socket creation " + std::to_string(WSAGetLastError()));
    }

    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(address.c_str());
    service.sin_port = htons(port);

    if (listening and bind(socket_descriptor, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        throw std::domain_error("Error in socket binding " + std::to_string(WSAGetLastError()));
    }

};