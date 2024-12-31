cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_library(ili9486_hal_pico)

target_sources(ili9486_hal_pico PRIVATE ili9486_hal_pico.c)

target_include_directories(ili9486_hal_pico PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ili9486_hal_pico PUBLIC
    ili9486_driver
    pico_stdlib
)