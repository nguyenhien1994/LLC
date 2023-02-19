#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "LineLengthCounter.hpp"
#include "utils.hpp"

void validate(const std::string& filename, size_t chunk_size) {
    std::cout << "------------" << filename << "---------" << std::endl;

    LineLengthCounter llc(filename, chunk_size);

    auto start_llc = nanotime();
    auto llc_result = llc.count();
    auto end_llc = nanotime();

    std::cout << "runtime ms with llc: " << delta_ms(start_llc, end_llc) << " ms" << std::endl;

    auto start_normal = nanotime();
    auto normal_result = count_normal(filename);
    auto end_normal = nanotime();
    std::cout << "runtime ms with normal: " << delta_ms(start_normal, end_normal) << " ms" << std::endl;

    if (llc_result != normal_result) {
        std::cout << "------test FAILED------" << std::endl;
        std::cout << "llc_result: " << llc_result.size() << std::endl;
        std::cout << "normal_result: " << normal_result.size() << std::endl;
    }
}

int main() {
    validate("/home/hiennm/projects/github/LargeFileReader/tests/input1kb.txt", 100);
    validate("/home/hiennm/projects/github/LargeFileReader/tests/input100kb.txt", 16 * 1024);
    validate("/home/hiennm/projects/github/LargeFileReader/tests/input100MB.txt", 1024 * 1024);
    validate("/home/hiennm/projects/github/LargeFileReader/tests/input1GB.txt", 10 * 1024 * 1024);
    validate("/home/hiennm/projects/github/LargeFileReader/tests/input10GB.txt", 100 * 1024 * 1024);
    return EXIT_SUCCESS;
}