add_library(nproto "src/nproto_service.c")
add_library(${PROJECT_NAMESPACE}::networking::nproto ALIAS nproto)
target_include_directories(nproto PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/utilities>")
target_link_libraries(nproto INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS nproto
        EXPORT networking-nproto-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/networking"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT networking-nproto-targets
        FILE ${PROJECT_EXPORT_NAME}-networking-nproto-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::networking::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/networking")
endif()

add_library(tproto "src/tproto_service.c")
add_library(${PROJECT_NAMESPACE}::networking::tproto ALIAS tproto)
target_include_directories(tproto PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/utilities>")
target_link_libraries(tproto INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS tproto
        EXPORT networking-tproto-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/networking"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT networking-tproto-targets
        FILE ${PROJECT_EXPORT_NAME}-networking-tproto-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::networking::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/networking")
endif()

add_library(networking-socket2 "src/socket2.c")
add_library(${PROJECT_NAMESPACE}::networking::socket2 ALIAS networking-socket2)
target_include_directories(networking-socket2 PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/utilities>")
target_link_libraries(networking-socket2 PUBLIC nproto)
target_link_libraries(networking-socket2 PUBLIC tproto)
target_link_libraries(networking-socket2 PRIVATE utilities-misc)
target_link_libraries(networking-socket2 PRIVATE utilities-try)
target_link_libraries(networking-socket2 INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS networking-socket2
        EXPORT networking-socket2-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/networking"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT networking-socket2-targets
        FILE ${PROJECT_EXPORT_NAME}-networking-socket2-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::networking::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/networking")
endif()


add_library(nproto-ipv4 "src/nproto/nproto_service_ipv4.c")
add_library(${PROJECT_NAMESPACE}::networking::nproto-ipv4 ALIAS nproto-ipv4)
target_include_directories(nproto-ipv4 PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/utilities>")
target_link_libraries(nproto-ipv4 PUBLIC nproto)
target_link_libraries(nproto-ipv4 PRIVATE utilities-misc)
target_link_libraries(nproto-ipv4 PRIVATE utilities-try)
target_link_libraries(nproto-ipv4 INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS nproto-ipv4
        EXPORT networking-nproto-ipv4
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/networking"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT networking-nproto-ipv4
        FILE ${PROJECT_EXPORT_NAME}-networking-nproto-ipv4-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::networking::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/networking")
endif()


add_library(nproto-unix "src/nproto/nproto_service_unix.c")
add_library(${PROJECT_NAMESPACE}::networking::nproto-unix ALIAS nproto-unix)
target_include_directories(nproto-unix PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/utilities>")
target_link_libraries(nproto-unix PUBLIC nproto)
target_link_libraries(nproto-unix PRIVATE utilities-misc)
target_link_libraries(nproto-unix PRIVATE utilities-try)
target_link_libraries(nproto-unix INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS nproto-unix
        EXPORT networking-nproto-unix
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/networking"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT networking-nproto-unix
        FILE ${PROJECT_EXPORT_NAME}-networking-nproto-unix-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::networking::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/networking")
endif()

add_library(tproto-tcp "src/tproto/tproto_service_tcp.c")
add_library(${PROJECT_NAMESPACE}::networking::tproto-tcp ALIAS tproto-tcp)
target_include_directories(tproto-tcp PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/utilities>")
target_link_libraries(tproto-tcp PRIVATE utilities-misc)
target_link_libraries(tproto-tcp PRIVATE utilities-try)
target_link_libraries(tproto-tcp INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS tproto-tcp
        EXPORT networking-tproto-tcp
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/networking"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT networking-tproto-tcp
        FILE ${PROJECT_EXPORT_NAME}-networking-tproto-tcp-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::networking::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/networking")
endif()

if (LIBCOMMON_BUILD_TESTS)
    add_subdirectory("test")
endif ()
