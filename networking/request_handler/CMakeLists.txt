add_library(networking-request-handler "src/request_handler.c")
target_include_directories(networking-request-handler PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(networking-request-handler PUBLIC networking-socket2)
set_target_properties(networking-request-handler PROPERTIES PREFIX ${LIBCOMMON_LIBRARY_PREFIX})
