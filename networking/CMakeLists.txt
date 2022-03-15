add_subdirectory(request_handler)
add_subdirectory(communication_manager)
add_subdirectory(socket2)

add_library(networking INTERFACE)
target_link_libraries(networking INTERFACE networking-communication-manager)
target_link_libraries(networking INTERFACE networking-socket2)
target_link_libraries(networking INTERFACE networking-request-handler)

if(LIBCOMMON_INSTALL)
    install(TARGETS
            networking
            networking-communication-manager
            networking-socket2
            nproto
            tproto
            nproto-ipv4
            nproto-unix
            tproto-tcp
            networking-request-handler
            coverage_config
        EXPORT networking-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
       
    install(DIRECTORY
            "${CMAKE_CURRENT_SOURCE_DIR}/communication-manager/include/"
            "${CMAKE_CURRENT_SOURCE_DIR}/socket2/include/"
            "${CMAKE_CURRENT_SOURCE_DIR}/request-handler/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBCOMMON_INCLUDEDIR}/networking"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT networking-targets
        FILE ${LIBCOMMON_EXPORT_NAME}-networking-targets.cmake
        NAMESPACE ${LIBCOMMON_NAMESPACE}::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${LIBCOMMON_EXPORT_NAME}")
endif()
