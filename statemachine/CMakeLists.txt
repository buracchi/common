add_library(statemachine
    "src/statemachine.c")

add_library(${PROJECT_NAMESPACE}::statemachine ALIAS statemachine)

target_compile_definitions(statemachine PRIVATE STATEMACHINE_VERSION=1)

target_include_directories(statemachine PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/statemachine>")

target_link_libraries(statemachine PRIVATE utilities-try)
target_link_libraries(statemachine INTERFACE coverage_config)

if (LIBCOMMON_BUILD_TESTS)
    add_subdirectory("test")
endif ()

if(LIBCOMMON_INSTALL)
    install(TARGETS statemachine
        EXPORT statemachine-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/statemachine"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT statemachine-targets
        FILE ${PROJECT_EXPORT_NAME}-statemachine-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}")
endif()
