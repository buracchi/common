add_subdirectory(communication_manager)
add_subdirectory(socket2)

add_library(networking STATIC
    $<TARGET_OBJECTS:networking-communication-manager>
    $<TARGET_OBJECTS:networking-socket2>
    $<TARGET_OBJECTS:nproto>
    $<TARGET_OBJECTS:tproto>
    $<TARGET_OBJECTS:nproto-ipv4>
    $<TARGET_OBJECTS:nproto-unix>
    $<TARGET_OBJECTS:tproto-tcp>)
target_link_libraries(networking PUBLIC networking-communication-manager)
target_link_libraries(networking PUBLIC networking-socket2)
target_link_libraries(networking PUBLIC nproto)
target_link_libraries(networking PUBLIC tproto)
target_link_libraries(networking PUBLIC nproto-ipv4)
target_link_libraries(networking PUBLIC nproto-unix)
target_link_libraries(networking PUBLIC tproto-tcp)
set_target_properties(networking PROPERTIES PREFIX ${LIBCOMMON_LIBRARY_PREFIX})

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
        EXPORT networking-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
       
    install(DIRECTORY
            "${CMAKE_CURRENT_SOURCE_DIR}/communication_manager/include/"
            "${CMAKE_CURRENT_SOURCE_DIR}/socket2/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT networking-targets
        FILE ${LIBCOMMON_EXPORT_NAME}-networking-targets.cmake
        NAMESPACE ${LIBCOMMON_NAMESPACE}::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${LIBCOMMON_EXPORT_NAME}")
endif()
