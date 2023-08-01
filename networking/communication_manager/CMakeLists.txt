find_package(Libevent CONFIG REQUIRED)

add_library(networking-communication-manager
            OBJECT
            "src/communication_manager.c")
target_include_directories(networking-communication-manager PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(networking-communication-manager PUBLIC networking-socket2)
target_link_libraries(networking-communication-manager PRIVATE nproto-ipv4)
target_link_libraries(networking-communication-manager PRIVATE tproto-tcp)
if (WIN32)
    target_link_libraries(networking-communication-manager PRIVATE libevent::core libevent::extra)
else ()
    target_link_libraries(networking-communication-manager PRIVATE libevent::core libevent::extra libevent::pthreads)
endif (WIN32)
target_link_libraries(networking-communication-manager PRIVATE concurrency)
target_link_libraries(networking-communication-manager PRIVATE utilities)
set_target_properties(networking-communication-manager PROPERTIES PREFIX ${LIBCOMMON_LIBRARY_PREFIX})

if (LIBCOMMON_BUILD_TESTS)
    add_subdirectory("test")
endif ()
