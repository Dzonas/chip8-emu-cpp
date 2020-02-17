cmake_minimum_required(VERSION 3.13)
project(chip8_emu_cpp)
set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

enable_testing()
add_subdirectory(src)
add_subdirectory(tests)

add_custom_target(
        docs ALL
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs
        COMMAND doxygen
        VERBATIM
)

install(
        TARGETS chip8_emu_cpp
        CONFIGURATIONS Debug Release
        DESTINATION bin)

install(DIRECTORY resources/
        CONFIGURATIONS Debug Release
        DESTINATION resources)