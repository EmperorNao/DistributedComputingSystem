#ifndef DISTRIBUTEDCOMPUTINGSYSTEM_DISTRIBUTABLE_H
#define DISTRIBUTEDCOMPUTINGSYSTEM_DISTRIBUTABLE_H


#include <vector>
#include <string>
#include <map>


namespace SCM {

    using FileData = std::vector<std::string>;
    using MetaInfo = FileData;
    using Query = FileData;
    using Key = FileData;
    using SplittedData = std::map<Query, FileData>;
    using ComputedData = std::map<Key, FileData>;

    struct split_output {
        SplittedData data;
        FileData meta_info;
    };
    struct compute_output {
        Key key;
        FileData output;
    };
    struct merge_output {
        FileData data;
    };


    class Distributable {

        virtual void split(FileData data_to_split, uint64_t number_of_workers) = 0;
        virtual void compute(Query query, FileData data_to_compute, MetaInfo meta_data) = 0;
        virtual void merge(Key key, FileData data_to_merge) = 0;

    };

}


#endif //DISTRIBUTEDCOMPUTINGSYSTEM_DISTRIBUTABLE_H
