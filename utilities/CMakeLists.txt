if (${UNIX})
add_subdirectory(argparser)
endif(${UNIX})
add_subdirectory(misc)
add_subdirectory(try)

add_library(utilities INTERFACE)

add_library(buracchi::${PROJECT_NAME}::utilities ALIAS utilities)

target_compile_definitions(utilities INTERFACE UTILITIES_VERSION=1)

if (${UNIX})
	target_link_libraries(utilities INTERFACE utilities-argparser)
endif(${UNIX})
target_link_libraries(utilities INTERFACE utilities-misc)
target_link_libraries(utilities INTERFACE utilities-try)

if(LIBCOMMON_INSTALL)
    install(TARGETS utilities
        EXPORT utilitiesTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
       
    install(EXPORT utilitiesTargets
        FILE ${PROJECT_NAME}_utilitiesTargets.cmake
        NAMESPACE buracchi::${PROJECT_NAME}::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}")
endif()
