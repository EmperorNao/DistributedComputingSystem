#include "ControlMessage.h"

void network::DataMessage::save(std::string filename) const {

    std::ofstream file(filename);
    //if type == MessageType::DataMessage
    //file.write(reinterpret_cast<char*>(filenames.size()), sizeof(std::size_t));
    file << filenames.size() << "\n";
    for (auto& el: filenames) {
        file << el << "\n";
    }
    file.close();

}

void network::DataMessage::load(std::string filename) {

    std::ifstream file(filename);
    //file.read(reinterpret_cast<char*>(type), sizeof(type));

    std::size_t number_of_files;
    //file.read(reinterpret_cast<char*>(number_of_files), sizeof(std::size_t));
    std::string buf;
    std::getline(file, buf);
    if (not buf.empty())
        number_of_files = std::stoull(buf);

    filenames.resize(number_of_files);

    for (int i = 0; i < number_of_files; ++i) {
        std::getline(file, filenames[i]);
    }

    file.close();

}
