cmake_minimum_required(VERSION 3.0)
project(LineLengthCounter)

##################
# Compiler setting
##################
if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# We require a C++17 compliant compiler
set(CMAKE_CXX_STANDARD_REQUIRED ON)

########################
# Build executable files
########################
add_executable(LineLengthCounter src/main.cpp src/LineLengthCounter.cpp src/LineLengthCounter.hpp src/ThreadPool.hpp)

########################
# Build test program
########################
add_executable(generate_text_file tests/generate_text_file.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(LineLengthCounter PRIVATE Threads::Threads)
