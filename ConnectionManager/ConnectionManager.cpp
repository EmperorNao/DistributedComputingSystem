#include "ConnectionManager.h"


void network::ConnectionManager::receive() {

    if (config.threading) {
        std::thread t(inner_receive, this->config);
        return;
    }
    inner_receive(this->config);

}


void network::ConnectionManager::inner_receive(network::ConnectionConfig config) {

    sockaddr_in sender_address;
    int sender_address_size = sizeof(sender_address);

    sender_address.sin_family = AF_INET;
    sender_address.sin_port = htons(config.current_port);
    sender_address.sin_addr.s_addr = inet_addr(config.current_address.c_str());

    std::vector<int8_t> receive_buffer(config.packet_size);
    Socket s(config.current_address, config.current_port, false);

    if (connect(s.get_descriptor(), (SOCKADDR*)&sender_address, sizeof(sender_address)) == SOCKET_ERROR) {
        throw std::domain_error("Error in receive " + err());
    }

    FileSendable obj(config.filename);

    int64_t size = 0;
    while (true) {

        int64_t received_bytes = recv(s.get_descriptor(), reinterpret_cast<char*>(receive_buffer.data()), config.packet_size, 0);
        if (received_bytes <= 0) {
            break;
        }
        size += received_bytes;
        obj.append(receive_buffer);

        if (size > (std::numeric_limits<int64_t>::max() / 2)) {
            obj.save(size);
            size = 0;
        }

    };
    obj.save(size);

}


void network::ConnectionManager::listening_and_sending() {

    if (config.threading) {
        std::thread t(inner_listening_and_sending, this->config);
        return;
    }
    inner_listening_and_sending(this->config);

}


void network::ConnectionManager::inner_listening_and_sending(network::ConnectionConfig config) {

    Socket main_socket(config.current_address, config.current_port, true);
    listen(main_socket.get_descriptor(), SOMAXCONN);

    while (config.send_inf or config.nums_to_send > 0) {

        struct sockaddr addr;
        int len = sizeof(addr);
        SOCKET accept_descriptor;

        accept_descriptor = accept(main_socket.get_descriptor(), &addr, &len);
        if (accept_descriptor == INVALID_SOCKET) {
            throw std::domain_error("Error in socket accept " + err());
        }
        std::shared_ptr<Socket> accept_socket = std::make_shared<Socket>(accept_descriptor);

        std::thread t(send_with_socket, config.filename, accept_socket, config.packet_size);
        t.detach();
        config.nums_to_send -= 1;

    }

}


void network::ConnectionManager::send_with_socket(std::string filename, std::shared_ptr<Socket> s, int64_t packet_size) {

    FileSendable obj(std::move(filename));
    obj.set_size(packet_size);

    for (auto el: obj) {

        if (send(
                s->get_descriptor(),
                reinterpret_cast<char *>(el.data()),
                el.size(),
                0) == SOCKET_ERROR) {
            throw std::domain_error("Error in sending with socket " + err());

        }

    }

}
