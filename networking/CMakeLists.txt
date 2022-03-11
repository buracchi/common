add_subdirectory(request_handler)
add_subdirectory(communication_manager)
add_subdirectory(socket2)

add_library(networking INTERFACE)

add_library(${PROJECT_NAMESPACE}::networking ALIAS networking)

target_compile_definitions(networking INTERFACE NETWORKING_VERSION=1)

target_link_libraries(networking INTERFACE networking-socket2)
target_link_libraries(networking INTERFACE networking-request-handler)

if(LIBCOMMON_INSTALL)
    install(TARGETS networking
        EXPORT networking-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
       
    install(EXPORT networking-targets
        FILE ${PROJECT_EXPORT_NAME}-networking-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}")
endif()
