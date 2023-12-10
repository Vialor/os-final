cmake_minimum_required(VERSION 3.10)

project(RDWR VERSION 1.0.0)
add_executable(run run.c rdwr.c tools.c)
add_executable(run2 run2.c rdwr.c tools.c)
add_executable(caching caching.c rdwr.c tools.c)
add_executable(system_call system_call.c rdwr.c tools.c)
add_executable(fast fast.c)

# add_subdirectory("library/benchmark")
# add_compile_options("-std=c++11 -isystem benchmark/include\
#     -Lbenchmark/build/src -lbenchmark -lpthread")
# add_executable(runbenchmark runbenchmark.cpp rdwr.c)
# target_link_libraries(runbenchmark benchmark::benchmark)