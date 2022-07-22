add_executable(
        test_socket2
        "socket2.cpp"
)
target_link_libraries(test_socket2 PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(test_socket2 PRIVATE networking)
gtest_add_tests(TARGET test_socket2)
