#include "MatrixProduct.h"
#include <algorithm>


int main(int argc, char** argv) {

/*    int start_position = 2;

    int n_jobs = std::stoull(argv[1]);

    std::vector<std::string> key;
    std::vector<std::string> data;

    for (int i = 0; i < n_jobs; ++i) {
        key.push_back(parse_args(argv, argc, start_position)[0]);
        //auto key = parse_args(argv, argc, start_position);
        data.push_back(parse_args(argv, argc, start_position)[0]);


    }
    std::sort(key.begin(), key.end());
    std::sort(data.begin(), data.end());
    MatrixProduct task;
    //task.compute(query, data);
    //task.split(data, std::stoull(argv[start_position]));
    task.merge(key, data);*/

    int start_position = 1;

    auto data = parse_args(argv, argc, start_position);

    MatrixProduct task;
    task.split(data, std::stoull(argv[start_position]));



}
