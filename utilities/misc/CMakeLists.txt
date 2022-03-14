add_library(utilities-misc "src/utilities.c")
target_include_directories(utilities-misc PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/utilities>")
target_link_libraries(utilities-misc INTERFACE coverage_config)
