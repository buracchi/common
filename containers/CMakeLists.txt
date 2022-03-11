add_library(containers INTERFACE)

add_library(${PROJECT_NAMESPACE}::containers ALIAS containers)

target_compile_definitions(containers INTERFACE CONTAINERS_VERSION=1)

target_link_libraries(containers INTERFACE containers-list)
target_link_libraries(containers INTERFACE containers-stack)
target_link_libraries(containers INTERFACE containers-queue)
target_link_libraries(containers INTERFACE containers-map)
target_link_libraries(containers INTERFACE containers-linked-list)
target_link_libraries(containers INTERFACE containers-linked-list-stack)
target_link_libraries(containers INTERFACE containers-double-linked-list-stack-queue)
target_link_libraries(containers INTERFACE containers-linked-list-map)

add_library(containers-list "src/list.c")
add_library(${PROJECT_NAMESPACE}::containers::list ALIAS containers-list)
target_include_directories(containers-list PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/containers>")
target_link_libraries(containers-list PUBLIC iterators)
target_link_libraries(containers-list INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS containers-list
        EXPORT containers-list-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/containers"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT containers-list-targets
        FILE ${PROJECT_EXPORT_NAME}-containers-list-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::containers::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/containers")
endif()

add_library(containers-stack "src/stack.c")
add_library(${PROJECT_NAMESPACE}::containers::stack ALIAS containers-stack)
target_include_directories(containers-stack PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/containers>")
target_link_libraries(containers-stack INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS containers-stack
        EXPORT containers-stack-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/containers"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT containers-stack-targets
        FILE ${PROJECT_EXPORT_NAME}-containers-stack-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::containers::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/containers")
endif()

add_library(containers-queue "src/queue.c")
add_library(${PROJECT_NAMESPACE}::containers::queue ALIAS containers-queue)
target_include_directories(containers-queue PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/containers>")
target_link_libraries(containers-queue INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS containers-queue
        EXPORT containers-queue-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/containers"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT containers-queue-targets
        FILE ${PROJECT_EXPORT_NAME}-containers-queue-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::containers::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/containers")
endif()

add_library(containers-map "src/map.c")
add_library(${PROJECT_NAMESPACE}::containers::map ALIAS containers-map)
target_include_directories(containers-map PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/containers>")
target_link_libraries(containers-map PUBLIC iterators)
target_link_libraries(containers-map INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS containers-map
        EXPORT containers-map-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/containers"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT containers-map-targets
        FILE ${PROJECT_EXPORT_NAME}-containers-map-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::containers::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/containers")
endif()


add_library(containers-linked-list
    "src/list/linked_list.c"
    "src/list/linked_list_element.c"
    "src/list/linked_list_iterator.c")
add_library(${PROJECT_NAMESPACE}::containers::linked-list ALIAS containers-linked-list)
target_include_directories(containers-linked-list PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/containers>")
target_link_libraries(containers-linked-list PUBLIC containers-list)
target_link_libraries(containers-linked-list PRIVATE utilities-try)
target_link_libraries(containers-linked-list INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS containers-linked-list
        EXPORT containers-linked-list-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/containers"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT containers-linked-list-targets
        FILE ${PROJECT_EXPORT_NAME}-containers-linked-list-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::containers::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/containers")
endif()

add_library(containers-linked-list-stack
    "src/stack/linked_list_stack.c")
add_library(${PROJECT_NAMESPACE}::containers::linked-list-stack ALIAS containers-linked-list-stack)
target_include_directories(containers-linked-list-stack PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/containers>")
target_link_libraries(containers-linked-list-stack PUBLIC containers-stack)
target_link_libraries(containers-linked-list-stack PRIVATE containers-linked-list)
target_link_libraries(containers-linked-list-stack PRIVATE utilities-try)
target_link_libraries(containers-linked-list-stack INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS containers-linked-list-stack
        EXPORT containers-linked-list-stack-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/containers"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT containers-linked-list-stack-targets
        FILE ${PROJECT_EXPORT_NAME}-containers-linked-list-stack-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::containers::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/containers")
endif()

add_library(containers-double-linked-list-stack-queue
    "src/queue/double_linked_list_stack_queue.c")
add_library(${PROJECT_NAMESPACE}::containers::double-linked-list-stack-queue ALIAS containers-double-linked-list-stack-queue)
target_include_directories(containers-double-linked-list-stack-queue PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/containers>")
target_link_libraries(containers-double-linked-list-stack-queue PUBLIC containers-queue)
target_link_libraries(containers-double-linked-list-stack-queue PRIVATE containers-linked-list-stack)
target_link_libraries(containers-double-linked-list-stack-queue PRIVATE utilities-try)
target_link_libraries(containers-double-linked-list-stack-queue INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS containers-double-linked-list-stack-queue
        EXPORT containers-double-linked-list-stack-queue-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/containers"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT containers-double-linked-list-stack-queue-targets
        FILE ${PROJECT_EXPORT_NAME}-containers-double-linked-list-stack-queue-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::containers::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/containers")
endif()

add_library(containers-linked-list-map
    "src/map/linked_list_map.c")
add_library(${PROJECT_NAMESPACE}::containers::linked-list-map ALIAS containers-linked-list-map)
target_compile_definitions(containers-linked-list-map PRIVATE CONTAINERS_VERSION=1)
target_include_directories(containers-linked-list-map PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/containers>")
target_link_libraries(containers-linked-list-map PUBLIC containers-map)
target_link_libraries(containers-linked-list-map PRIVATE containers-linked-list)
target_link_libraries(containers-linked-list-map PRIVATE utilities-misc)
target_link_libraries(containers-linked-list-map PRIVATE utilities-try)
target_link_libraries(containers-linked-list-map INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS containers-linked-list-map
        EXPORT containers-linked-list-map-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/containers"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT containers-linked-list-map-targets
        FILE ${PROJECT_EXPORT_NAME}-containers-linked-list-map-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::containers::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/containers")
endif()

if (LIBCOMMON_BUILD_TESTS)
    add_subdirectory("test")
endif ()

if(LIBCOMMON_INSTALL)
    install(TARGETS containers
        EXPORT containers-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
       
    install(EXPORT containers-targets
        FILE ${PROJECT_EXPORT_NAME}-containers-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}")
endif()
