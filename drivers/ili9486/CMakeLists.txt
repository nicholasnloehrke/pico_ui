cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_library(ili9486_driver)

target_sources(ili9486_driver PRIVATE ili9486_driver.c)

target_include_directories(ili9486_driver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
