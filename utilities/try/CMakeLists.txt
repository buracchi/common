add_library(utilities-try INTERFACE)

add_library(buracchi::${PROJECT_NAME}::utilities::try ALIAS utilities-try)

target_include_directories(utilities-try INTERFACE 
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/utilities>")

target_link_libraries(utilities-try INTERFACE coverage_config)

if(LIBCOMMON_INSTALL)
    install(TARGETS utilities-try
        EXPORT utilities-tryTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/utilities"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT utilities-tryTargets
        FILE ${PROJECT_NAME}_utilities-tryTargets.cmake
        NAMESPACE buracchi::${PROJECT_NAME}::utilities::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}/utilities")
endif()
