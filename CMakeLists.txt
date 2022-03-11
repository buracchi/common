cmake_minimum_required (VERSION 3.16)

option(LIBCOMMON_BUILD_TESTS "Build test programs" ON)
option(LIBCOMMON_INSTALL "Generate installation target" ON)
option(LIBCOMMON_ENABLE_TEST_COVERAGE "Enable coverage reporting" OFF)

include("${CMAKE_CURRENT_SOURCE_DIR}/.cmake/vcpkg.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/.cmake/gtest.cmake")
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

project ("libcommon" VERSION 0.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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

add_library(coverage_config INTERFACE)

if (LIBCOMMON_ENABLE_TEST_COVERAGE)
    target_compile_options(coverage_config INTERFACE -O0 -g --coverage)
    target_link_options(coverage_config INTERFACE --coverage)
endif ()
if(LIBCOMMON_INSTALL)
    install(TARGETS coverage_config EXPORT coverage_configTargets)
    install(EXPORT coverage_configTargets DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/")
endif()

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

# Configure CMake find_package() config files

if(LIBCOMMON_INSTALL)
    configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/.cmake/${PROJECT_NAME}Config.cmake.in"
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION
        "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}")
    
    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        DESTINATION
        "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}")
endif()
