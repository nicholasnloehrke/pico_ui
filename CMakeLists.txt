# Generated Cmake Pico project file
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add FreeRTOS kernel
include(FetchContent)
FetchContent_Declare(freertos_kernel
GIT_REPOSITORY https://github.com/raspberrypi/FreeRTOS-Kernel.git
    GIT_TAG 4f7299d # Note: Best practice to use specific git-hash or tagged version
)
FetchContent_MakeAvailable(freertos_kernel)
add_library(freertos_config INTERFACE)





# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
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

# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico_ui C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_subdirectory(drivers/ili9486)
add_subdirectory(drivers/ili9486/platforms/pico)
add_subdirectory(lvgl)
add_subdirectory(src)

# Add executable. Default name is the project name, version 0.1
add_executable(pico_ui main.c)

pico_set_program_name(pico_ui "pico_ui")
pico_set_program_version(pico_ui "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(pico_ui 0)
pico_enable_stdio_usb(pico_ui 1)

target_include_directories(freertos_config SYSTEM
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR} # Replace with the actual path to FreeRTOSConfig.h
)
target_compile_definitions(freertos_config
    PUBLIC
    projCOVERAGE_TEST=0
)

# Add the standard library to the build
target_link_libraries(pico_ui
    pico_stdlib
    src_lib
    freertos_kernel
    freertos_config
)

# Add the standard include files to the build
target_include_directories(pico_ui PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(pico_ui)
