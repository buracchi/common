add_library(utilities-argparser
    "src/argparser.c"
    "src/parser.c"
    "src/usage.c")

add_library(${PROJECT_NAMESPACE}::utilities::argparser ALIAS utilities-argparser)

target_include_directories(utilities-argparser PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/utilities>")

target_link_libraries(utilities-argparser PUBLIC containers-map)
target_link_libraries(utilities-argparser PRIVATE containers-linked-list)
target_link_libraries(utilities-argparser PRIVATE containers-linked-list-map)
target_link_libraries(utilities-argparser PRIVATE utilities-misc)
target_link_libraries(utilities-argparser PRIVATE utilities-try)
target_link_libraries(utilities-argparser INTERFACE coverage_config)

if (LIBCOMMON_BUILD_TESTS)
    add_subdirectory("test")
endif ()

if(LIBCOMMON_INSTALL)
    install(TARGETS utilities-argparser
        EXPORT utilities-argparser-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/utilities"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT utilities-argparser-targets
        FILE ${PROJECT_EXPORT_NAME}-utilities-argparser-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::utilities::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/utilities")
endif()
