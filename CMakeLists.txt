cmake_minimum_required (VERSION 3.16)

option(LIBCOMMON_BUILD_TESTS "Build test programs" ON)
option(LIBCOMMON_INSTALL "Generate installation target" ON)

include("${CMAKE_CURRENT_SOURCE_DIR}/.cmake/vcpkg.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/.cmake/gtest.cmake")
include(GNUInstallDirs)

project ("libcommon" VERSION 0.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Debug configuration

if (CMAKE_BUILD_TYPE MATCHES DEBUG)
    if (MSVC)
        add_compile_options(/Wall /Wx /fsanitize=address)
    else ()
        add_compile_options(-Wall -Wextra -pedantic -fms-extensions -fsanitize=address)
        add_link_options(-fsanitize=address)
    endif (MSVC)
endif (CMAKE_BUILD_TYPE MATCHES DEBUG)

# Guards

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
    FATAL_ERROR
    "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif()

# Test

if (LIBCOMMON_BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    # Notice that GTest::GTest and GTest::Main are deprecated since CMake 3.20 
    # and should be replaced with GTest::gtest and GTest::gtest_main but this
    # will make CMake 3.16.3 fails.
endif ()

# Code Coverage Configuration

option(ENABLE_TEST_COVERAGE "Enable coverage reporting" OFF)

add_library(coverage_config INTERFACE)

if (ENABLE_TEST_COVERAGE)
    target_compile_options(coverage_config INTERFACE -O0 -g --coverage)
    target_link_options(coverage_config INTERFACE --coverage)
endif ()

# Subprojects

if (${UNIX})
    add_subdirectory("concurrency")
endif(${UNIX})
add_subdirectory("containers")
add_subdirectory("iterators")
if (${UNIX})
    add_subdirectory("networking")
endif(${UNIX})
add_subdirectory("statemachine")
add_subdirectory("utilities")
