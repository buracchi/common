add_library(containers STATIC
    $<TARGET_OBJECTS:containers-list>
    $<TARGET_OBJECTS:containers-stack>
    $<TARGET_OBJECTS:containers-queue>
    $<TARGET_OBJECTS:containers-map>
    $<TARGET_OBJECTS:containers-linked-list>
    $<TARGET_OBJECTS:containers-linked-list-stack>
    $<TARGET_OBJECTS:containers-double-linked-list-stack-queue>
    $<TARGET_OBJECTS:containers-linked-list-map>)
target_link_libraries(containers PUBLIC containers-list)
target_link_libraries(containers PUBLIC containers-stack)
target_link_libraries(containers PUBLIC containers-queue)
target_link_libraries(containers PUBLIC containers-map)
target_link_libraries(containers PUBLIC containers-linked-list)
target_link_libraries(containers PUBLIC containers-linked-list-stack)
target_link_libraries(containers PUBLIC containers-double-linked-list-stack-queue)
target_link_libraries(containers PUBLIC containers-linked-list-map)
set_target_properties(containers PROPERTIES PREFIX ${LIBCOMMON_LIBRARY_PREFIX})

add_library(containers-list OBJECT "src/list.c")
target_include_directories(containers-list PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(containers-list PUBLIC iterators)
target_link_libraries(containers-list INTERFACE coverage_config)

add_library(containers-stack OBJECT "src/stack.c")
target_include_directories(containers-stack PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(containers-stack INTERFACE coverage_config)

add_library(containers-queue OBJECT "src/queue.c")
target_include_directories(containers-queue PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(containers-queue INTERFACE coverage_config)

add_library(containers-map OBJECT "src/map.c")
target_include_directories(containers-map PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(containers-map PUBLIC iterators)
target_link_libraries(containers-map INTERFACE coverage_config)

add_library(containers-linked-list OBJECT
    "src/list/linked_list.c"
    "src/list/linked_list_element.c"
    "src/list/linked_list_iterator.c")
target_include_directories(containers-linked-list PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(containers-linked-list PUBLIC containers-list)
target_link_libraries(containers-linked-list PRIVATE utilities)
target_link_libraries(containers-linked-list INTERFACE coverage_config)

add_library(containers-linked-list-stack OBJECT "src/stack/linked_list_stack.c")
target_include_directories(containers-linked-list-stack PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(containers-linked-list-stack PUBLIC containers-stack)
target_link_libraries(containers-linked-list-stack PRIVATE containers-linked-list)
target_link_libraries(containers-linked-list-stack PRIVATE utilities)
target_link_libraries(containers-linked-list-stack INTERFACE coverage_config)

add_library(containers-double-linked-list-stack-queue OBJECT
    "src/queue/double_linked_list_stack_queue.c")
target_include_directories(containers-double-linked-list-stack-queue PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(containers-double-linked-list-stack-queue PUBLIC containers-queue)
target_link_libraries(containers-double-linked-list-stack-queue PRIVATE containers-linked-list-stack)
target_link_libraries(containers-double-linked-list-stack-queue PRIVATE utilities)
target_link_libraries(containers-double-linked-list-stack-queue INTERFACE coverage_config)

add_library(containers-linked-list-map OBJECT "src/map/linked_list_map.c")
target_compile_definitions(containers-linked-list-map PRIVATE CONTAINERS_VERSION=1)
target_include_directories(containers-linked-list-map PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(containers-linked-list-map PUBLIC containers-map)
target_link_libraries(containers-linked-list-map PRIVATE containers-linked-list)
target_link_libraries(containers-linked-list-map PRIVATE utilities)
target_link_libraries(containers-linked-list-map INTERFACE coverage_config)

if (LIBCOMMON_BUILD_TESTS)
    add_subdirectory("test")
endif ()

if(LIBCOMMON_INSTALL)
    install(TARGETS
            containers
            containers-list
            containers-stack
            containers-queue
            containers-map
            containers-linked-list
            containers-linked-list-stack
            containers-double-linked-list-stack-queue
            containers-linked-list-map
            coverage_config
        EXPORT containers-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBCOMMON_INCLUDEDIR}/containers"
            FILES_MATCHING PATTERN "*.h*")

    install(EXPORT containers-targets
        FILE ${LIBCOMMON_EXPORT_NAME}-containers-targets.cmake
        NAMESPACE ${LIBCOMMON_NAMESPACE}::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${LIBCOMMON_EXPORT_NAME}")
endif()
