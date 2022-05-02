#ifndef DISTRIBUTEDCOMPUTINGSYSTEM_ISENDABLE_H
#define DISTRIBUTEDCOMPUTINGSYSTEM_ISENDABLE_H


#include <iostream>
#include <utility>
#include <vector>

#include <string>
#include <fstream>
#include <iostream>

#include <iterator>


namespace network {

    class FileIterator {

        using pointer = std::vector<int8_t> *;  // or also value_type*
        using reference = std::vector<int8_t> &;  // or also value_type&

        int64_t size;
        std::vector<int8_t> content;
        std::ifstream file;
        bool pos;

        void step() {

            if (not pos)
                return;
            file.read(reinterpret_cast<char *>(content.data()), this->size);
            this->content.resize(file.gcount());
            pos = not this->content.empty();

        }


    public:

        explicit FileIterator(const std::string &filename, int64_t _size = 1, bool _pos = false) :
                file(filename, std::ios::binary),
                size(_size),
                pos(_pos),
                content(size) {
            step();
        }

        virtual reference operator*() { return content; };

        pointer operator->() { return &content; }

        FileIterator &operator++() {
            this->step();
            return *this;
        }

        friend bool operator==(const FileIterator &a, const FileIterator &b) { return a.pos == b.pos; };

        friend bool operator!=(const FileIterator &a, const FileIterator &b) { return a.pos != b.pos; };

    };


    class FileSendable {


        std::string filename;
        int64_t size;
        std::vector<int8_t> current;


    public:

        explicit FileSendable(std::string fname, int64_t _size = 1) :
                filename(std::move(fname)),
                size(_size) {}

        void set_size(int64_t _size) { size = _size; }

        [[nodiscard]] int64_t get_size() const { return size; }

        FileIterator begin() { return FileIterator(filename, size, true); };

        FileIterator end() { return FileIterator(filename, size, false); };

        void append(std::vector<int8_t> data) {

            current.insert(current.end(), data.begin(), data.end());

        }

        void save(int64_t bytes_to_save = -1, bool append = true) {

            if (bytes_to_save < 0) {
                bytes_to_save = current.size();
            }


            std::ofstream file;
            if (append) {
                file.open(filename, std::ios_base::app | std::ios::binary);
            }
            else {
                file.open(filename);
            }

            std::copy(current.begin(), current.begin() + bytes_to_save, std::ostreambuf_iterator<char>(file));
            file.close();
            current.resize(0);

        }

    };

}


#endif //DISTRIBUTEDCOMPUTINGSYSTEM_ISENDABLE_H