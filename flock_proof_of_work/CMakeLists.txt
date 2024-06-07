cmake_minimum_required(VERSION 3.15)
project(flock_prof_of_work LANGUAGES CXX)
find_package(Threads REQUIRED)

add_executable(flock_prof_of_work "main.cpp")
target_link_libraries(flock_prof_of_work Threads::Threads)
