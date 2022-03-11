add_library(containers INTERFACE)

add_library(buracchi::${PROJECT_NAME}::containers ALIAS containers)

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
add_library(buracchi::${PROJECT_NAME}::containers::list ALIAS containers-list)
target_include_directories(containers-list PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/containers>")
target_link_libraries(containers-list PUBLIC iterators)
target_link_libraries(containers-list INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS containers-list
        EXPORT containers-listTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/containers"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT containers-listTargets
        FILE ${PROJECT_NAME}_containers-listTargets.cmake
        NAMESPACE buracchi::${PROJECT_NAME}::containers::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}/containers")
endif()

add_library(containers-stack "src/stack.c")
add_library(buracchi::${PROJECT_NAME}::containers::stack ALIAS containers-stack)
target_include_directories(containers-stack PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/containers>")
target_link_libraries(containers-stack INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS containers-stack
        EXPORT containers-stackTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/containers"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT containers-stackTargets
        FILE ${PROJECT_NAME}_containers-stackTargets.cmake
        NAMESPACE buracchi::${PROJECT_NAME}::containers::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}/containers")
endif()

add_library(containers-queue "src/queue.c")
add_library(buracchi::${PROJECT_NAME}::containers::queue ALIAS containers-queue)
target_include_directories(containers-queue PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/containers>")
target_link_libraries(containers-queue INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS containers-queue
        EXPORT containers-queueTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/containers"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT containers-queueTargets
        FILE ${PROJECT_NAME}_containers-queueTargets.cmake
        NAMESPACE buracchi::${PROJECT_NAME}::containers::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}/containers")
endif()

add_library(containers-map "src/map.c")
add_library(buracchi::${PROJECT_NAME}::containers::map ALIAS containers-map)
target_include_directories(containers-map PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/containers>")
target_link_libraries(containers-map PUBLIC iterators)
target_link_libraries(containers-map INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS containers-map
        EXPORT containers-mapTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/containers"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT containers-mapTargets
        FILE ${PROJECT_NAME}_containers-mapTargets.cmake
        NAMESPACE buracchi::${PROJECT_NAME}::containers::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}/containers")
endif()


add_library(containers-linked-list
    "src/list/linked_list.c"
    "src/list/linked_list_element.c"
    "src/list/linked_list_iterator.c")
add_library(buracchi::${PROJECT_NAME}::containers::linked-list ALIAS containers-linked-list)
target_include_directories(containers-linked-list PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/containers>")
target_link_libraries(containers-linked-list PUBLIC containers-list)
target_link_libraries(containers-linked-list PRIVATE utilities-try)
target_link_libraries(containers-linked-list INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS containers-linked-list
        EXPORT containers-linked-listTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/containers"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT containers-linked-listTargets
        FILE ${PROJECT_NAME}_containers-linked-listTargets.cmake
        NAMESPACE buracchi::${PROJECT_NAME}::containers::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}/containers")
endif()

add_library(containers-linked-list-stack
    "src/stack/linked_list_stack.c")
add_library(buracchi::${PROJECT_NAME}::containers::linked-list-stack ALIAS containers-linked-list-stack)
target_include_directories(containers-linked-list-stack PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/containers>")
target_link_libraries(containers-linked-list-stack PUBLIC containers-stack)
target_link_libraries(containers-linked-list-stack PRIVATE containers-linked-list)
target_link_libraries(containers-linked-list-stack PRIVATE utilities-try)
target_link_libraries(containers-linked-list-stack INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS containers-linked-list-stack
        EXPORT containers-linked-list-stackTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/containers"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT containers-linked-list-stackTargets
        FILE ${PROJECT_NAME}_containers-linked-list-stackTargets.cmake
        NAMESPACE buracchi::${PROJECT_NAME}::containers::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}/containers")
endif()

add_library(containers-double-linked-list-stack-queue
    "src/queue/double_linked_list_stack_queue.c")
add_library(buracchi::${PROJECT_NAME}::containers::double-linked-list-stack-queue ALIAS containers-double-linked-list-stack-queue)
target_include_directories(containers-double-linked-list-stack-queue PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/containers>")
target_link_libraries(containers-double-linked-list-stack-queue PUBLIC containers-queue)
target_link_libraries(containers-double-linked-list-stack-queue PRIVATE containers-linked-list-stack)
target_link_libraries(containers-double-linked-list-stack-queue PRIVATE utilities-try)
target_link_libraries(containers-double-linked-list-stack-queue INTERFACE coverage_config)
if(LIBCOMMON_INSTALL)
    install(TARGETS containers-double-linked-list-stack-queue
        EXPORT containers-double-linked-list-stack-queueTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/containers"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT containers-double-linked-list-stack-queueTargets
        FILE ${PROJECT_NAME}_containers-double-linked-list-stack-queueTargets.cmake
        NAMESPACE buracchi::${PROJECT_NAME}::containers::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}/containers")
endif()

add_library(containers-linked-list-map
    "src/map/linked_list_map.c")
add_library(buracchi::${PROJECT_NAME}::containers::linked-list-map ALIAS containers-linked-list-map)
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
        EXPORT containers-linked-list-mapTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/containers"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT containers-linked-list-mapTargets
        FILE ${PROJECT_NAME}_containers-linked-list-mapTargets.cmake
        NAMESPACE buracchi::${PROJECT_NAME}::containers::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}/containers")
endif()

if (LIBCOMMON_BUILD_TESTS)
    add_subdirectory("test")
endif ()

if(LIBCOMMON_INSTALL)
    install(TARGETS containers
        EXPORT containersTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
       
    install(EXPORT containersTargets
        FILE ${PROJECT_NAME}_containersTargets.cmake
        NAMESPACE buracchi::${PROJECT_NAME}::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}")
endif()
