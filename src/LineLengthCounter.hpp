#pragma once
#include <vector>
#include <thread>

struct ChunkResult {
    // [line number] -> length of the line
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
    std::vector<ChunkResult> chunk_results_;
    std::vector<std::thread> workers_;

    void chunk_counter(size_t);
    void merge_consecutive_chunks(const ChunkResult&, ChunkResult&);
    std::vector<size_t> merge_chunk_results();
};