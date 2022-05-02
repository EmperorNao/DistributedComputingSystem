#include "exec.h"


namespace scheme {

#ifdef WIN32

    void call(std::string program_path, std::string args) {
        system(std::string(program_path + " " + args).c_str());
    }

#elif UNIX
    #include <unistd.h>
    void call(std::string program_path, std::string args) {
        scheme(program_path + " " + args);
# TODO
    }

#endif

    std::vector<std::string> extract_lines(std::string filename) {

        std::vector<std::string> lines;
        std::ifstream file(filename);

        uint64_t number_of_files = 0;
        std::string buf;
        std::getline(file, buf);
        if (not buf.empty())
            number_of_files = std::stoull(buf);

        lines.resize(number_of_files);

        for (int i = 0; i < number_of_files; ++i) {
            std::getline(file, lines[i]);
        }

        file.close();
        return lines;

    }


    std::string construct_eval_string(std::vector<std::string> &files) {

        std::string res;

        res += std::to_string(files.size()) + " ";
        for (auto &q: files) {
            res += q + " ";
        }

        return res;

    }



    bool is_number(char *s) {

        char* p;
        strtol(s, &p, 10);
        return *p == 0;

    }


    std::vector<std::string> parse_args(char **args, int number_of_args, int& start_position) {

        while (start_position < number_of_args) {

            if (is_number(args[++start_position])) {

                int64_t number_of_files = std::stoll(args[start_position]);
                std::vector<std::string> res(number_of_files);

                for (int64_t i = 0; i < number_of_files; ++i) {
                    res[i] = std::string(args[++start_position]);
                }
                return res;

            }
            else {

                return {std::string(args[start_position - 1])};

            }

        }

    }


}