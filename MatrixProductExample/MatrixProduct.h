#ifndef MATRIXPRODUCTEXAMPLE_MATRIXPRODUCT_H
#define MATRIXPRODUCTEXAMPLE_MATRIXPRODUCT_H


#include <iostream>
#include <fstream>
#include "Distributable.h"

#include <cmath>


class MatrixProduct {


public:


    void read_matrix(std::string filename, std::vector<int64_t> &matrix, int64_t &m, int64_t &n) {

        std::ifstream file(filename);

        file >> m >> n;
        matrix.resize(m * n);

        for (int64_t i = 0; i < m * n; ++i) {
            file >> matrix[i];
        }

    }


    void write_matrix(std::string filename, const std::vector<int64_t> &matrix, int64_t m, int64_t n) {

        std::ofstream file(filename);

        file << m << " " << n << "\n";

        for (int64_t i = 0; i < m; ++i) {
            for (int64_t j = 0; j < n; ++j) {

                file << matrix[i * n + j] << " ";

            }
            file << "\n";
        }

    }


    void split(SCM::FileData data_to_split, uint64_t number_of_workers) {

        ////////////////////////////////////////////////////////////////////////
        // DATA TO SPLIT
        // first file - first matrix
        // second file - second matrix
        ///////////////////////////////////////////////////////////////////////

        auto matrix1_fname = data_to_split[0];
        auto matrix2_fname = data_to_split[1];

        int64_t m1, n1, m2, n2;

        std::vector<int64_t> matrix1;
        std::vector<int64_t> matrix2;

        read_matrix(matrix1_fname, matrix1, m1, n1);
        read_matrix(matrix2_fname, matrix2, m2, n2);


        int64_t step_x = static_cast<int64_t>(std::ceil(double(m1) / number_of_workers));
        int64_t step_y = static_cast<int64_t>(std::ceil(double(n2) / number_of_workers));


        std::ofstream query_file("query");
        std::ofstream data_file("query_data");

        std::ofstream real_data("matrixes");
        real_data << 2 << "\n";
        real_data << matrix1_fname << "\n";
        real_data << matrix2_fname << "\n";


        int64_t iter = 0;
        if (step_x > step_y) {

            int64_t n_lines = static_cast<int64_t>(std::ceil(double(m1) / step_x));
            query_file << n_lines << "\n";
            data_file << n_lines << "\n";

            int64_t b;
            for (b = 0; b + step_x < m1; b += step_x) {

                std::ofstream query("query" + std::to_string(iter));
                std::ofstream real_query("query" + std::to_string(iter) + "real");
                std::ofstream real_data("query" + std::to_string(iter) + "_datareal");

                query << b << " " << b + step_x << " " << 0 << " "<< n2;

                query_file << "query" + std::to_string(iter) + "real\n";
                data_file << "query" + std::to_string(iter) + "_datareal\n";
                real_data << 2 << "\n" << matrix1_fname << "\n" << matrix2_fname << "\n";
                real_query << 1 << "\n" << "query" + std::to_string(iter);

                iter += 1;

            }

            std::ofstream query("query" + std::to_string(iter));
            std::ofstream real_query("query" + std::to_string(iter) + "real");
            std::ofstream real_data("query" + std::to_string(iter) + "_datareal");
            query << b << " " << m1 << " " << 0 << " " << n2;
            query_file << "query" + std::to_string(iter) + "real\n";
            data_file << "query" + std::to_string(iter) + "_datareal\n";
            real_query << 1 << "\n" << "query" + std::to_string(iter);
            real_data << 2 << "\n" << matrix1_fname << "\n" << matrix2_fname << "\n";

            iter += 1;


        } else {

            int64_t n_lines = static_cast<int64_t>(std::ceil(double(n2) / step_y));
            query_file << n_lines << "\n";
            data_file << n_lines << "\n";

            int64_t l;
            for (l = 0; l + step_y < n2; l += step_y) {

                std::ofstream query("query" + std::to_string(iter));
                std::ofstream real_query("query" + std::to_string(iter) + "real");
                std::ofstream real_data("query" + std::to_string(iter) + "_datareal");
                query << 0 << " " << m1 << " " << l << " " << l + step_y;

                query_file << "query" + std::to_string(iter) + "real\n";
                data_file << "query" + std::to_string(iter) + "_datareal\n";
                real_query << 1 << "\n" << "query" + std::to_string(iter);
                real_data << 2 << "\n" << matrix1_fname << "\n" << matrix2_fname << "\n";

                iter += 1;

            }

            std::ofstream query("query" + std::to_string(iter));
            std::ofstream real_query("query" + std::to_string(iter) + "real");
            std::ofstream real_data("query" + std::to_string(iter) + "_datareal");
            query << 0 << " " << m1 << " " << l << " " << n2;
            query_file << "query" + std::to_string(iter) + "real\n";
            data_file << "query" + std::to_string(iter) + "_datareal\n";
            real_query << 1 << "\n" << "query" + std::to_string(iter);

            real_data << 2 << "\n" << matrix1_fname << "\n" << matrix2_fname << "\n";

            iter += 1;

        }

        ////////////////////////////////////////////////////////////////////////
        // SPLITTED DATA
        // Query - 4 numbers
        // top bottom left right border - values to be computed in final matrix
        // Data - same files as to split
        ///////////////////////////////////////////////////////////////////////

    }

    void compute(SCM::Query query, SCM::FileData data_to_compute) {

        std::ifstream file(query[0]);

        int64_t t, b, l, r;
        file >> b >> t >> l >> r;


        auto matrix1_fname = data_to_compute[0];
        auto matrix2_fname = data_to_compute[1];

        int64_t m1, n1, m2, n2;

        std::vector<int64_t> matrix1;
        std::vector<int64_t> matrix2;

        read_matrix(matrix1_fname, matrix1, m1, n1);
        read_matrix(matrix2_fname, matrix2, m2, n2);

        std::vector<int64_t> matrix3(m1 * n2);

        std::ofstream ofile;

        ofile.open("data");
        ofile << 1 << "\n";
        ofile << query[0] + "_data";
        ofile.close();

        ofile.open("key");
        ofile << 1 << "\n" << query[0] + "_key";
        ofile.close();\

        ofile.open(query[0] + "_key");
        ofile << b << " " << t << " " << l << " " << r;

        std::ofstream out(query[0] + "_data");

        //std::ofstream key("key");

        //key << b << " " << t << " " << l << " " << r;

        out << m1 << " " << n2 << "\n";
        for (int64_t i = b; i < t; ++i) {
            for (int64_t j = l; j < r; ++j) {

                int64_t sum = 0;
                for (int64_t k = 0; k < m2; ++k) {

                    sum += matrix1[i * n1 + k] * matrix2[k * n2 + j];

                }
                out << sum << " ";

            }
            out << "\n";

        }

    }

    void merge(SCM::Key key, SCM::FileData data_to_merge) {

        std::vector<int64_t> matrix;

        std::ifstream in(data_to_merge[0]);

        int64_t t, b, l, r;
        int64_t m, n;
        in >> m >> n;
        matrix.resize(m * n);

        std::ifstream key_file;
        std::ifstream data;

        for (int64_t i = 0; i < key.size(); ++i) {

            key_file.open(key[i]);
            data.open(data_to_merge[i]);

            key_file >> b >> t >> l >> r;
            data >> m >> n;
            for (int64_t y = l; y < r; ++y)
                for (int64_t x = b; x < t; ++x)
                    data >> matrix[x * n + y];

            key_file.close();
            data.close();

        }

        write_matrix("output", matrix, m, n);

    }


};


bool is_number(char *s);


std::vector<std::string> parse_args(char **args, int number_of_args, int& start_position);



#endif //MATRIXPRODUCTEXAMPLE_MATRIXPRODUCT_H
