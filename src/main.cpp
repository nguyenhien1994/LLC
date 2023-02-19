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

    std::cout << "Runtime with LLC: " << delta_ms(start_llc, end_llc) << " ms" << std::endl;

    auto start_brute_force = nanotime();
    auto brute_force = count_brute_force(filename);
    auto end_brute_force = nanotime();
    std::cout << "Runtime with brute-force: " << delta_ms(start_brute_force, end_brute_force) << " ms" << std::endl;

    if (llc_result != brute_force) {
        std::cout << "------test FAILED------" << std::endl;
        std::cout << "LLC_result lines: " << llc_result.size() << std::endl;
        std::cout << "brute_force lines: " << brute_force.size() << std::endl;
    }
}

int main (int argc, char** argv) {
    if (argc != 3) {
        std::cout << "USAGE: " << argv[0] << " <input file> <chunk size in bytes> " << std::endl;
        return EXIT_FAILURE;
    }

    auto input_file = std::string(argv[1]);
    auto chunk_size = atol(argv[2]);

    validate(input_file, chunk_size);
    return EXIT_SUCCESS;
}