add_library(utilities-misc OBJECT "src/utilities.c")
target_include_directories(utilities-misc PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(utilities-misc INTERFACE coverage_config)
set_target_properties(utilities-misc PROPERTIES PREFIX ${LIBCOMMON_LIBRARY_PREFIX})
