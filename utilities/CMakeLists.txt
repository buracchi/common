if (${UNIX})
add_subdirectory(argparser)
endif(${UNIX})
add_subdirectory(misc)
add_subdirectory(try)

add_library(utilities INTERFACE)
target_compile_definitions(utilities INTERFACE UTILITIES_VERSION=1)
if (${UNIX})
	target_link_libraries(utilities INTERFACE utilities-argparser)
endif(${UNIX})
target_link_libraries(utilities INTERFACE utilities-misc)
target_link_libraries(utilities INTERFACE utilities-try)

if(LIBCOMMON_INSTALL)
    install(EXPORT utilities-tryTargets
        FILE utilities-tryTargets.cmake
        NAMESPACE buracchi::${PROJECT_NAME}::utilities::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/")
    install(EXPORT utilities-miscTargets
        FILE utilities-miscTargets.cmake
        NAMESPACE buracchi::${PROJECT_NAME}::utilities::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/")
endif()
