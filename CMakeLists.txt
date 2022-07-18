cmake_minimum_required (VERSION 3.21)

option(LIBCOMMON_BUILD_TESTS "Build test programs" ON)
option(LIBCOMMON_INSTALL "Generate installation target" ON)
option(LIBCOMMON_ENABLE_TEST_COVERAGE "Enable coverage reporting" OFF)

if (LIBCOMMON_INSTALL)
    include(GNUInstallDirs)
    include(CMakePackageConfigHelpers)
endif ()
if (LIBCOMMON_BUILD_TESTS)
    list(APPEND VCPKG_MANIFEST_FEATURES "tests")
    include(GoogleTest)
endif ()

project ("common" VERSION 0.1)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
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
    find_package(GTest CONFIG REQUIRED)
endif ()

# Code Coverage Configuration

add_library(coverage_config INTERFACE)

if (LIBCOMMON_ENABLE_TEST_COVERAGE)
    target_compile_options(coverage_config INTERFACE -O0 -g --coverage)
    target_link_options(coverage_config INTERFACE --coverage)
endif ()

# Configure CMake find_package() config files

if(LIBCOMMON_INSTALL)
    set(LIBCOMMON_EXPORT_NAME "buracchi-${PROJECT_NAME}")
    set(LIBCOMMON_NAMESPACE "buracchi::${PROJECT_NAME}")
    set(LIBCOMMON_LIBRARY_PREFIX "libburacchi-${PROJECT_NAME}-")

    configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/config.cmake.in"
        "${PROJECT_BINARY_DIR}/${LIBCOMMON_EXPORT_NAME}-config.cmake"
        INSTALL_DESTINATION
        "${CMAKE_INSTALL_DATAROOTDIR}/${LIBCOMMON_EXPORT_NAME}")
    
    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${LIBCOMMON_EXPORT_NAME}-config.cmake"
        DESTINATION
        "${CMAKE_INSTALL_DATAROOTDIR}/${LIBCOMMON_EXPORT_NAME}")
endif()

# Subprojects

if (${UNIX})
    add_subdirectory("concurrency")
    add_subdirectory("networking")
endif(${UNIX})
add_subdirectory("argparser")
add_subdirectory("containers")
add_subdirectory("logger")
add_subdirectory("iterators")
add_subdirectory("statemachine")
add_subdirectory("utilities")
