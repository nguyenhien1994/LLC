#pragma once
#include <vector>
#include <thread>

struct CounterResult {
    // [line] -> length
    std::vector<size_t> lines_counter;

    char first_char;
    char end_char;
};

class LineLengthCounter {
public:
    LineLengthCounter(const std::string& filename, size_t chunk_size);
    std::vector<size_t> count();

private:
    int fd_;
    size_t file_size_;
    size_t nbr_chunks_;
    size_t chunk_size_;
    size_t last_chunk_size_;

    std::vector<std::thread> workers_;

    CounterResult chunk_counter(size_t);
    std::vector<size_t> merge_chunk_results(const std::vector<CounterResult>&);
};