add_executable(
        test_statemachine
        "statemachine.cpp"
)
target_link_libraries(test_statemachine PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(test_statemachine PRIVATE statemachine)
gtest_discover_tests(test_statemachine)
