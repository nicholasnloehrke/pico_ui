cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_library(lvgl)

file(GLOB_RECURSE LVGL_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

target_sources(lvgl PUBLIC ${LVGL_SRC})

target_include_directories(lvgl PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(lvgl PUBLIC
    ili9486_driver
    ili9486_hal_pico
)
