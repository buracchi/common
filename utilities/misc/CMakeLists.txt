add_library(utilities-misc "src/utilities.c")

add_library(buracchi::${PROJECT_NAME}::utilities::misc ALIAS utilities-misc)

target_include_directories(utilities-misc PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/utilities>")

target_link_libraries(utilities-misc INTERFACE coverage_config)

if(LIBCOMMON_INSTALL)
    install(TARGETS utilities-misc
        EXPORT utilities-miscTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/utilities"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT utilities-miscTargets
        FILE ${PROJECT_NAME}_utilities-miscTargets.cmake
        NAMESPACE buracchi::${PROJECT_NAME}::utilities::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}/utilities")
endif()
