#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
#include <unordered_map>

#include "LineLengthCounter.hpp"
#include "utils.hpp"

LineLengthCounter::LineLengthCounter(const std::string& filename, size_t chunk_size) {
    fd_ = open(filename.c_str(), O_RDONLY);
    file_size_ = get_file_size(fd_);
    chunk_size_ = chunk_size;
    nbr_chunks_ = file_size_ / chunk_size_;
    last_chunk_size_ =  file_size_ % chunk_size_;
    if (last_chunk_size_ != 0) {
        nbr_chunks_++;
    }
}

std::vector<size_t> LineLengthCounter::count() {
    std::vector<CounterResult> res(nbr_chunks_);
    for (size_t i = 0; i < nbr_chunks_; ++i) {
        res[i] = std::move(this->chunk_counter(i));
    }

    return merge_chunk_results(res);
}

CounterResult LineLengthCounter::chunk_counter(size_t chunk_number) {
    CounterResult result;
    std::string buffer;
    size_t start_offset = chunk_number * chunk_size_;
    size_t total_chars = chunk_number == (nbr_chunks_ - 1) ? last_chunk_size_ : chunk_size_;
    buffer.resize(total_chars);

    auto len = pread(fd_, &buffer[0], total_chars, start_offset);
    if (len != total_chars) {
        std::cout << "WARN: pread return length != required length: " << len << std::endl;
        std::cerr << "errno: " << std::strerror(errno) << std::endl;
    }
    result.first_char = buffer[0];
    result.end_char = buffer[len-1];
    {
        std::stringstream ss(buffer);
        std::string line;
        size_t line_number = 0;
        // std::cout << "chunk: " << chunk_number << std::endl;
        // std::cout << "------" << std::endl;
        // std::cout << "\tbuffer: " << buffer << std::endl;
        while (std::getline(ss, line)) {
            result.lines_counter.push_back(line.length());
            // std::cout << "\t\t - line: " << line_number << " - len: " << line.length() << std::endl;
            line_number++;
        }
        // std::cout << "\t\t\t - first_char: " << result.first_char << " - end_char: " << result.end_char << "\n\n";
        // std::cout << "------" << std::endl;
    }

    return result;
}

void merge_consecutive_chunks(const CounterResult& from, CounterResult& to) {
    if (from.lines_counter.size() == 0) {
        // nothing to merge
        return;
    }
    size_t from_idx = 0;
    if (to.end_char != '\n') {
        to.lines_counter[to.lines_counter.size()-1] += from.lines_counter[0];
        from_idx++;
    }
    for (; from_idx < from.lines_counter.size(); ++from_idx) {
        to.lines_counter.emplace_back(from.lines_counter[from_idx]);
    }

    to.end_char = from.end_char;
}

std::vector<size_t> LineLengthCounter::merge_chunk_results(const std::vector<CounterResult>& res_results) {
    CounterResult res(res_results[0]);
    for (size_t i = 1; i < res_results.size(); i++) {
        merge_consecutive_chunks(res_results[i], res);
    }

    return res.lines_counter;
}
