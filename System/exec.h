#ifndef DISTRIBUTEDCOMPUTINGSYSTEM_EXEC_H
#define DISTRIBUTEDCOMPUTINGSYSTEM_EXEC_H


#include <vector>
#include <iostream>
#include <fstream>
#include <string>


namespace scheme {

    void call(std::string program_path, std::string args);

    std::vector<std::string> extract_lines(std::string filename);

    std::string construct_eval_string(std::vector<std::string> &files);

    bool is_number(char* s);

    std::vector<std::string> parse_args(char **args, int number_of_args, int& start_position);

}


#endif //DISTRIBUTEDCOMPUTINGSYSTEM_EXEC_H
