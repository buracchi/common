find_package(Libevent CONFIG REQUIRED)

add_library(networking-communication-manager "src/communication_manager.c")

add_library(${PROJECT_NAMESPACE}::networking::communication-manager ALIAS networking-communication-manager)

target_include_directories(networking-communication-manager PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/utilities>")

target_link_libraries(networking-communication-manager PUBLIC networking-request-handler)
target_link_libraries(networking-communication-manager PRIVATE networking-socket2)
target_link_libraries(networking-communication-manager PRIVATE nproto-ipv4)
target_link_libraries(networking-communication-manager PRIVATE tproto-tcp)
if (${WIN32})
    target_link_libraries(networking-communication-manager PRIVATE libevent::core libevent::extra)
else()
    target_link_libraries(networking-communication-manager PRIVATE libevent::core libevent::extra libevent::pthreads)
endif()
target_link_libraries(networking-communication-manager PRIVATE concurrency-tpool)
target_link_libraries(networking-communication-manager PRIVATE utilities-misc)
target_link_libraries(networking-communication-manager PRIVATE utilities-try)

if (LIBCOMMON_BUILD_TESTS)
    add_subdirectory("test")
endif ()

if(LIBCOMMON_INSTALL)
    install(TARGETS networking-communication-manager
        EXPORT networking-communication-manager-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/networking"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT networking-communication-manager-targets
        FILE ${PROJECT_EXPORT_NAME}-networking-communication-manager-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::networking::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/networking")
endif()
