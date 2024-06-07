cmake_minimum_required(VERSION 3.5)

add_library(
        gvl
        gvl.cpp
)

target_include_directories(
        gvl
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

add_executable(
        gvl_example
        example.cpp
)

target_link_libraries(
        gvl_example
        gvl
)
