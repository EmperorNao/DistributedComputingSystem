#ifndef DISTRIBUTEDCOMPUTINGSYSTEM_CONTROLMESSAGE_H
#define DISTRIBUTEDCOMPUTINGSYSTEM_CONTROLMESSAGE_H


#include <iostream>
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
        uint64_t number_of_files;

    public:
        explicit DataMessage(uint64_t n_files):
        ControlMessage(MessageType::DataMessage),
        number_of_files(n_files) {}

        void save(std::string filename) const final;
        void load(std::string filename) final;
        [[nodiscard]] uint64_t get_number_of_files() const { return number_of_files; }

    };


}


#endif //DISTRIBUTEDCOMPUTINGSYSTEM_CONTROLMESSAGE_H
