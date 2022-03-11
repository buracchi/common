add_library(iterators "src/iterator.c")

add_library(buracchi::${PROJECT_NAME}::iterators ALIAS iterators)

target_compile_definitions(iterators PRIVATE ITERATORS_VERSION=1)

target_include_directories(iterators PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/iterators>")

target_link_libraries(iterators INTERFACE coverage_config)

if (LIBCOMMON_BUILD_TESTS)
    add_subdirectory("test")
endif ()

if(LIBCOMMON_INSTALL)
    install(TARGETS iterators
        EXPORT iteratorsTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/iterators"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT iteratorsTargets
        FILE ${PROJECT_NAME}_iteratorsTargets.cmake
        NAMESPACE buracchi::${PROJECT_NAME}::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}")
endif()
