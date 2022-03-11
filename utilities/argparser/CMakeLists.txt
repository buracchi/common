add_library(
        utilities-argparser
        STATIC
        "src/argparser.c"
        "src/parser.c"
        "src/usage.c"
)

add_library(buracchi::${PROJECT_NAME}::utilities::argparser ALIAS utilities-argparser)

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
        EXPORT utilities-argparserTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/utilities"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT utilities-argparserTargets
        FILE ${PROJECT_NAME}_utilities-argparserTargets.cmake
        NAMESPACE buracchi::${PROJECT_NAME}::utilities::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}/utilities")
endif()
