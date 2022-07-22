add_library(nproto OBJECT "src/nproto_service.c")
target_include_directories(nproto PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(nproto INTERFACE $<BUILD_INTERFACE:coverage_config>)
set_target_properties(nproto PROPERTIES PREFIX ${LIBCOMMON_LIBRARY_PREFIX})

add_library(tproto OBJECT "src/tproto_service.c")
target_include_directories(tproto PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(tproto INTERFACE $<BUILD_INTERFACE:coverage_config>)
set_target_properties(tproto PROPERTIES PREFIX ${LIBCOMMON_LIBRARY_PREFIX})

add_library(networking-socket2 OBJECT "src/socket2.c")
target_include_directories(networking-socket2 PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(networking-socket2 PUBLIC nproto)
target_link_libraries(networking-socket2 PUBLIC tproto)
target_link_libraries(networking-socket2 PRIVATE utilities-misc)
target_link_libraries(networking-socket2 PRIVATE utilities-try)
target_link_libraries(networking-socket2 INTERFACE $<BUILD_INTERFACE:coverage_config>)
set_target_properties(networking-socket2 PROPERTIES PREFIX ${LIBCOMMON_LIBRARY_PREFIX})

add_library(nproto-ipv4 OBJECT "src/nproto/nproto_service_ipv4.c")
target_include_directories(nproto-ipv4 PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(nproto-ipv4 PUBLIC nproto)
target_link_libraries(nproto-ipv4 PRIVATE utilities-misc)
target_link_libraries(nproto-ipv4 PRIVATE utilities-try)
target_link_libraries(nproto-ipv4 INTERFACE $<BUILD_INTERFACE:coverage_config>)
set_target_properties(nproto-ipv4 PROPERTIES PREFIX ${LIBCOMMON_LIBRARY_PREFIX})

add_library(nproto-unix OBJECT "src/nproto/nproto_service_unix.c")
target_include_directories(nproto-unix PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(nproto-unix PUBLIC nproto)
target_link_libraries(nproto-unix PRIVATE utilities-misc)
target_link_libraries(nproto-unix PRIVATE utilities-try)
target_link_libraries(nproto-unix INTERFACE $<BUILD_INTERFACE:coverage_config>)
set_target_properties(nproto-unix PROPERTIES PREFIX ${LIBCOMMON_LIBRARY_PREFIX})

add_library(tproto-tcp OBJECT "src/tproto/tproto_service_tcp.c")
target_include_directories(tproto-tcp PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(tproto-tcp PRIVATE utilities-misc)
target_link_libraries(tproto-tcp PRIVATE utilities-try)
target_link_libraries(tproto-tcp INTERFACE $<BUILD_INTERFACE:coverage_config>)
set_target_properties(tproto-tcp PROPERTIES PREFIX ${LIBCOMMON_LIBRARY_PREFIX})

if (LIBCOMMON_BUILD_TESTS)
    add_subdirectory("test")
endif ()
