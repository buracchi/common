add_executable(test_linked_list "list/linked_list.cpp")
target_link_libraries(test_linked_list PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(test_linked_list PRIVATE containers)
gtest_add_tests(TARGET test_linked_list)

add_executable(test_linked_list_stack "stack/linked_list_stack.cpp")
target_link_libraries(test_linked_list_stack PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(test_linked_list_stack PRIVATE containers)
gtest_add_tests(TARGET test_linked_list_stack)

add_executable(test_double_linked_list_stack_queue "queue/double_linked_list_stack_queue.cpp")
target_link_libraries(test_double_linked_list_stack_queue PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(test_double_linked_list_stack_queue PRIVATE containers)
gtest_add_tests(TARGET test_double_linked_list_stack_queue)

add_executable(test_linked_list_map "map/linked_list_map.cpp")
target_link_libraries(test_linked_list_map PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(test_linked_list_map PRIVATE containers)
gtest_add_tests(TARGET test_linked_list_map)
