cmake_minimum_required(VERSION 3.0.0)
project(pala VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(third_party/gflags)
add_subdirectory(third_party/googletest)
add_subdirectory(third_party/benchmark)

include_directories(src)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# base
add_library(pala_base
    src/flags.cc
    src/tools/scoped_shared_lock.cc
)
target_link_libraries(pala_base PUBLIC gflags::gflags)

# program
add_executable(pala
    src/main.cc
    src/worker.cc
    src/tools/random_generator.cc
)
target_link_libraries(pala PUBLIC
    pala_base
    Threads::Threads
)

# unittest
add_executable(pala_unittest
    unittest/unittest.cc
    src/worker.cc
)
target_compile_definitions(pala_unittest PRIVATE PALA_UNITTEST)
target_link_libraries(pala_unittest
    gtest_main
    pala_base
)

# benchmark
add_executable(pala_benchmark
    benchmark/benchmark.cc
    src/worker.cc
    src/tools/random_generator.cc
)
target_link_libraries(pala_benchmark PUBLIC
    benchmark::benchmark
    pala_base
)
