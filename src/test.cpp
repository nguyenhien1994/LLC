#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "LineLengthCounter.hpp"
#include "utils.hpp"

void test_small_file() {
    LineLengthCounter lc("/home/hiennm/projects/github/LargeFileReader/test_files/input1kb.txt", 100);

    auto start_lc = nanotime();
    auto lc_result = lc.count();
    auto end_lc = nanotime();

    std::cout << "delta_ns lc: " << delta_ns(start_lc, end_lc) << std::endl;

    auto start_normal = nanotime();
    auto normal_result = count_normal("/home/hiennm/projects/github/LargeFileReader/test_files/input1kb.txt");
    auto end_normal = nanotime();
    std::cout << "delta_ns normal: " << delta_ns(start_normal, end_normal) << std::endl;

    if (lc_result != normal_result) {
        std::cout << "------lc_result------" << std::endl;
        print_counter(lc_result);
        std::cout << "------lc_result------" << std::endl;

        std::cout << "------normal_result------" << std::endl;
        print_counter(normal_result);
        std::cout << "------normal_result------" << std::endl;
    }
}

void test_100kb_file() {
    LineLengthCounter lc("/home/hiennm/projects/github/LargeFileReader/test_files/input100kb.txt", 16 * 1024);

    auto start_lc = nanotime();
    auto lc_result = lc.count();
    auto end_lc = nanotime();

    std::cout << "delta_ns lc: " << delta_ns(start_lc, end_lc) << std::endl;

    auto start_normal = nanotime();
    auto normal_result = count_normal("/home/hiennm/projects/github/LargeFileReader/test_files/input100kb.txt");
    auto end_normal = nanotime();
    std::cout << "delta_ns normal: " << delta_ns(start_normal, end_normal) << std::endl;

    if (lc_result != normal_result) {
        std::cout << "------lc_result------" << std::endl;
        std::cout << lc_result.size() << std::endl;
        print_counter(lc_result);
        std::cout << "------lc_result------" << std::endl;

        std::cout << "------normal_result------" << std::endl;
        std::cout << normal_result.size() << std::endl;
        print_counter(normal_result);
        std::cout << "------normal_result------" << std::endl;
    }
}

void test_100MB_file() {
    LineLengthCounter lc("/home/hiennm/projects/github/LargeFileReader/test_files/input100MB.txt", 16 * 1024);

    auto start_lc = nanotime();
    auto lc_result = lc.count();
    auto end_lc = nanotime();

    std::cout << "delta_ns lc: " << delta_ns(start_lc, end_lc) << std::endl;

    auto start_normal = nanotime();
    auto normal_result = count_normal("/home/hiennm/projects/github/LargeFileReader/test_files/input100MB.txt");
    auto end_normal = nanotime();
    std::cout << "delta_ns normal: " << delta_ns(start_normal, end_normal) << std::endl;

    if (lc_result != normal_result) {
        std::cout << "------lc_result------" << std::endl;
        write_counter_to_file("lc_result.txt", lc_result);
        std::cout << lc_result.size() << std::endl;
        std::cout << "------lc_result------" << std::endl;

        std::cout << "------normal_result------" << std::endl;
        write_counter_to_file("normal_result.txt", normal_result);
        std::cout << normal_result.size() << std::endl;
        std::cout << "------normal_result------" << std::endl;
    }
}

int main() {
    test_small_file();
    test_100kb_file();
    test_100MB_file();
    return EXIT_SUCCESS;
}