
cmake_minimum_required(VERSION 3.16)

project(lb_Generator_Test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Основний файл програми
add_executable(lb_Generator_Test
    Generator.cpp
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/task.txt
    ${CMAKE_CURRENT_BINARY_DIR}/task.txt
    COPYONLY
)

