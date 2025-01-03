# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()

set(sdkVersion 2.1.0)
set(toolchainVersion RISCV_RPI_2_0_0_5)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)

if(EXISTS ${picoVscode})
    include(${picoVscode})
endif()

set(PICO_BOARD pico2 CACHE STRING "Board type")

include(pico_sdk_import.cmake)

project(pico_ui C CXX ASM)

pico_sdk_init()

include(FetchContent)

FetchContent_Declare(freertos_kernel
    GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
    GIT_TAG        main
)

FetchContent_MakeAvailable(freertos_kernel)

add_library(freertos_config INTERFACE)
target_include_directories(freertos_config INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/freertos_config
)

add_subdirectory(drivers/ili9486)
add_subdirectory(drivers/ili9486/platforms/pico)
add_subdirectory(lvgl)
add_subdirectory(src)

add_executable(pico_ui main.c)

pico_set_program_name(pico_ui "pico_ui")
pico_set_program_version(pico_ui "0.1")

pico_enable_stdio_uart(pico_ui 0)
pico_enable_stdio_usb(pico_ui 1)

target_link_libraries(pico_ui
    pico_stdlib
    src_lib
    freertos_kernel
    freertos_config
)

target_include_directories(pico_ui PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(pico_ui)
