cmake_minimum_required(VERSION 3.15)
project(sem_prof_of_concept LANGUAGES CXX)
find_package(Threads REQUIRED)

add_executable(sem_prof_of_concept "main.cpp")
target_link_libraries(sem_prof_of_concept Threads::Threads)
