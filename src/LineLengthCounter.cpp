#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
#include <unordered_map>

#include "LineLengthCounter.hpp"
#include "ThreadPool.hpp"
#include "utils.hpp"

LineLengthCounter::LineLengthCounter(const std::string& filename, size_t chunk_size) {
    fd_ = open(filename.c_str(), O_RDONLY);
    if (fd_ == -1) {
        std::cerr << "Failed to open file: " << filename << "errno: " << std::strerror(errno) << std::endl;
        return;
    }

    file_size_ = get_file_size(fd_);
    chunk_size_ = chunk_size;
    nbr_chunks_ = file_size_ / chunk_size_;
    last_chunk_size_ =  file_size_ % chunk_size_;
    if (last_chunk_size_ != 0) {
        nbr_chunks_++;
    } else {
        last_chunk_size_ = chunk_size_;
    }
    chunk_results_.resize(nbr_chunks_);
}

std::vector<size_t> LineLengthCounter::count() {
    {
        auto chunk_counter = [this](size_t chunk_number) {
            ChunkResult result;
            std::string buffer;
            size_t start_offset = chunk_number * chunk_size_;
            size_t required_size = chunk_number == (nbr_chunks_ - 1) ? last_chunk_size_ : chunk_size_;
            buffer.resize(required_size);

            // don't need to use any sync method here, pread will safe itself
            auto len = pread(this->fd_, &buffer[0], required_size, start_offset);
            if (len == -1) {
                std::cerr << "Failed to read chunk: " << chunk_number << "errno: " << std::strerror(errno) << std::endl;
                return;
            }
            result.end_char = buffer[len-1];
            {
                std::stringstream ss(buffer);
                std::string line;
                while (std::getline(ss, line)) {
                    result.lines_counter.push_back(line.length());
                }
            }

            this->chunk_results_[chunk_number] = std::move(result);
        };

        static const size_t max_workers = std::thread::hardware_concurrency();
        ThreadPool pool(std::min(max_workers, nbr_chunks_));
        for (size_t i = 0; i < nbr_chunks_; ++i) {
            pool.enqueue(chunk_counter, i);
        }
    }

    return merge_chunk_results();
}

// Merge 2 consecutive chunks
void LineLengthCounter::merge_consecutive_chunks(const ChunkResult& from, ChunkResult& to) {
    if (from.lines_counter.size() == 0) {
        // nothing to merge
        return;
    }
    size_t from_idx = 0;
    // if last char of 'to' chunk not end with '\n', it should be merged with first line of 'from' chunk
    if (to.end_char != '\n') {
        to.lines_counter[to.lines_counter.size()-1] += from.lines_counter[0];
        from_idx++;
    }
    for (; from_idx < from.lines_counter.size(); ++from_idx) {
        to.lines_counter.emplace_back(from.lines_counter[from_idx]);
    }

    to.end_char = from.end_char;
}

std::vector<size_t> LineLengthCounter::merge_chunk_results() {
    ChunkResult final_result(chunk_results_[0]);
    for (size_t i = 1; i < chunk_results_.size(); i++) {
        merge_consecutive_chunks(chunk_results_[i], final_result);
    }

    return final_result.lines_counter;
}
