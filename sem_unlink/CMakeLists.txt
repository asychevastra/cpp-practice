cmake_minimum_required(VERSION 3.15)
project(sem_unlink LANGUAGES CXX)
find_package(Threads REQUIRED)

add_executable(sem_unlink "main.cpp")
target_link_libraries(sem_unlink Threads::Threads)
