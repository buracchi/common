add_executable(
        test_communication_manager
        "communication_manager.cpp"
)
target_link_libraries(test_communication_manager PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(test_communication_manager PRIVATE networking)
gtest_discover_tests(test_communication_manager)
