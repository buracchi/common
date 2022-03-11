add_library(networking-request-handler "src/request_handler.c")

add_library(${PROJECT_NAMESPACE}::networking::request-handler ALIAS networking-request-handler)

target_include_directories(networking-request-handler PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/utilities>")

target_link_libraries(networking-request-handler PUBLIC networking-socket2)

if(LIBCOMMON_INSTALL)
    install(TARGETS networking-request-handler
        EXPORT networking-request-handler-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/networking"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT networking-request-handler-targets
        FILE ${PROJECT_EXPORT_NAME}-networking-request-handler-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::networking::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/networking")
endif()
