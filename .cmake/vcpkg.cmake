set(VCPKG_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
    
if(EXISTS ${VCPKG_TOOLCHAIN_FILE})    
    message(STATUS "Using vcpkg toolchain")
    set(CMAKE_TOOLCHAIN_FILE ${VCPKG_TOOLCHAIN_FILE} CACHE STRING "Vcpkg toolchain file")
endif()
