#ifndef DISTRIBUTEDCOMPUTINGSYSTEM_EXEC_H
#define DISTRIBUTEDCOMPUTINGSYSTEM_EXEC_H



#ifdef WIN32
#include <iostream>

void call(std::string program_path, std::string args) {
    system(std::string(program_path + " " + args).c_str());
}

#elif UNIX
#include <unistd.h>
void call(std::string program_path, std::string args) {
    system(program_path + " " + args);
    # TODO
}

#endif


#endif //DISTRIBUTEDCOMPUTINGSYSTEM_EXEC_H
