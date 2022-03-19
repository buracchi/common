add_library(iterators STATIC "src/iterator.c")

target_include_directories(iterators PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(iterators INTERFACE $<BUILD_INTERFACE:coverage_config>)
set_target_properties(iterators PROPERTIES PREFIX ${LIBCOMMON_LIBRARY_PREFIX})

if (LIBCOMMON_BUILD_TESTS)
    add_subdirectory("test")
endif ()

if(LIBCOMMON_INSTALL)
    install(TARGETS iterators
        EXPORT iterators-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT iterators-targets
        FILE ${LIBCOMMON_EXPORT_NAME}-iterators-targets.cmake
        NAMESPACE ${LIBCOMMON_NAMESPACE}::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${LIBCOMMON_EXPORT_NAME}")
endif()
