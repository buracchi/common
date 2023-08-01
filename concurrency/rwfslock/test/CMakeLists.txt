add_executable(
        test_rwfslock
        "rwfslock.cpp"
)
target_link_libraries(test_rwfslock PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(test_rwfslock PRIVATE concurrency-rwfslock)
gtest_discover_tests(test_rwfslock)
