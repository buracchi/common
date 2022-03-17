add_library(utilities-try INTERFACE)
target_include_directories(utilities-try INTERFACE 
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(utilities-try INTERFACE $<BUILD_INTERFACE:coverage_config>)
