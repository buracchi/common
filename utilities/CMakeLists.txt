add_subdirectory(misc)
add_subdirectory(try)

add_library(utilities INTERFACE)

add_library(${PROJECT_NAMESPACE}::utilities ALIAS utilities)

target_compile_definitions(utilities INTERFACE UTILITIES_VERSION=1)

target_link_libraries(utilities INTERFACE utilities-misc)
target_link_libraries(utilities INTERFACE utilities-try)

if(LIBCOMMON_INSTALL)
    install(TARGETS utilities
        EXPORT utilities-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
       
    install(EXPORT utilities-targets
        FILE ${PROJECT_EXPORT_NAME}-utilities-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}")
endif()
