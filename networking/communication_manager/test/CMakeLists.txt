add_executable(
        test_communication_manager
        "communication_manager.cpp"
)
target_link_libraries(test_communication_manager PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(test_communication_manager PRIVATE networking)
target_link_libraries(test_communication_manager PRIVATE utilities)
gtest_add_tests(TARGET test_communication_manager)
