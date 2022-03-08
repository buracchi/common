add_library(utilities-misc "src/utilities.c")
target_include_directories(utilities-misc PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/utilities>")
target_link_libraries(utilities-misc INTERFACE coverage_config)

if(LIBCOMMON_INSTALL)
    add_library(buracchi::${PROJECT_NAME}::utilities::misc ALIAS utilities-misc)
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/utilities"
        FILES_MATCHING PATTERN "*.h*")
    install(TARGETS utilities-misc
        EXPORT utilities-miscTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
endif()
