#ifndef DISTRIBUTEDCOMPUTINGSYSTEM_CONTROLMESSAGE_H
#define DISTRIBUTEDCOMPUTINGSYSTEM_CONTROLMESSAGE_H


#include <iostream>
#include <string>
#include <vector>
#include <fstream>


namespace network {

    enum class MessageType {DataMessage};


    class ControlMessage {

    protected:
        MessageType type;

    public:
        explicit ControlMessage(MessageType _type): type(_type) {}
        virtual void save(std::string filename) const = 0;
        virtual void load(std::string filename) = 0;

        [[nodiscard]] MessageType get_type() const { return type; }

    };


    class DataMessage: public ControlMessage {

    private:
        std::vector<std::string> filenames;

    public:
        explicit DataMessage(std::vector<std::string> fnames = {}):
        ControlMessage(MessageType::DataMessage),
        filenames(fnames)
        {}

        void save(std::string filename) const final;
        void load(std::string filename) final;
        [[nodiscard]] uint64_t get_number_of_files() const { return filenames.size(); }

        [[nodiscard]] std::vector<std::string> get_files() const { return filenames; }
        void set_files(std::vector<std::string> fnames) { filenames = fnames; }

    };


}


#endif //DISTRIBUTEDCOMPUTINGSYSTEM_CONTROLMESSAGE_H
