add_library(argparser
    "src/argparser.c"
    "src/parser.c"
    "src/usage.c")

add_library(${PROJECT_NAMESPACE}::argparser ALIAS argparser)

target_include_directories(argparser PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/argparser>")

target_link_libraries(argparser PUBLIC containers-map)
target_link_libraries(argparser PRIVATE containers-linked-list)
target_link_libraries(argparser PRIVATE containers-linked-list-map)
target_link_libraries(argparser PRIVATE utilities-misc)
target_link_libraries(argparser PRIVATE utilities-try)
target_link_libraries(argparser INTERFACE coverage_config)

if (LIBCOMMON_BUILD_TESTS)
    add_subdirectory("test")
endif ()

if(LIBCOMMON_INSTALL)
    install(TARGETS argparser
        EXPORT argparser-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/argparser"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT argparser-targets
        FILE ${PROJECT_EXPORT_NAME}-argparser-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}")
endif()
