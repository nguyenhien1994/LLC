#pragma once
#include <sys/stat.h>
#include <chrono>
#include <iostream>
#include <fstream>

inline size_t get_file_size(const int fd)
{
    struct stat file_stat;
    fstat(fd, &file_stat);
    // check errono
    return file_stat.st_size;
}

template<typename T>
void print_counter(const T& counter) {
    auto idx = 0;
    for (const auto& c : counter) {
        std::cout << "\t - line: " << idx << " - len: " << c << std::endl;
        idx++;
    }
}

template<typename T>
void write_counter_to_file(const std::string& outfile, const T& counter) {
    std::ofstream out;
    out.open(outfile);
    for (const auto& c : counter) {
        out << c << '\n';
    }
    out.close();
}

inline std::chrono::nanoseconds nanotime() {
    return std::chrono::high_resolution_clock::now().time_since_epoch();
}

inline unsigned long delta_ms(std::chrono::nanoseconds start, std::chrono::nanoseconds end) {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / 1e6;
}

inline std::vector<size_t> count_brute_force(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<size_t> result;
    std::string str; 
    while (std::getline(file, str)) {
        result.push_back(str.length());
    }

    return result;
}