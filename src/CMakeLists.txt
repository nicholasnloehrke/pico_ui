cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_SRC *.c)

add_library(src_lib)

target_sources(src_lib PUBLIC ${SRC_SRC})

target_include_directories(src_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(src_lib PUBLIC
    lvgl
)