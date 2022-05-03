#include "MatrixProduct.h"


bool is_number(char *s) {

    char* p;
    strtol(s, &p, 10);
    return *p == 0;

}


std::vector<std::string> parse_args(char **args, int number_of_args, int& start_position) {

    while (start_position < number_of_args) {

        if (is_number(args[start_position++])) {

            int64_t number_of_files = std::stoll(args[start_position - 1]);
            std::vector<std::string> res(number_of_files);

            for (int64_t i = 0; i < number_of_files; ++i) {
                res[i] = std::string(args[start_position++]);
            }
            return res;

        }
        else {

            return {std::string(args[start_position - 1])};

        }

    }

}