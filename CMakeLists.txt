cmake_minimum_required(VERSION 3.10)
project(Seminar4)

set(CMAKE_CXX_STANDARD 11)

# Основные исходные файлы
set(SOURCES
    main.cpp
    helpers.cpp
    tasks/task1.cpp
    tasks/task2.cpp
    tasks/task3.cpp
    tasks/task4.cpp
    tasks/task5.cpp
    tasks/task6.cpp
)

add_executable(seminar4 ${SOURCES})
