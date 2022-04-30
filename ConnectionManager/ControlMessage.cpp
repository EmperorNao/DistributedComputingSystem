#include "ControlMessage.h"

void network::DataMessage::save(std::string filename) const {

    std::ofstream file(filename);
    file.write(reinterpret_cast<char*>(type), sizeof(type));
    file.write(reinterpret_cast<char*>(number_of_files), sizeof(number_of_files));
    file.close();

}

void network::DataMessage::load(std::string filename) {

    std::ifstream file(filename);
    file.read(reinterpret_cast<char*>(type), sizeof(type));
    file.read(reinterpret_cast<char*>(number_of_files), sizeof(number_of_files));
    file.close();

}
