add_executable(
        test_utilities_strto
        "test_strto_short.cpp"
        "test_strto_int.cpp"
        "test_strto_long.cpp"
        "test_strto_long_long.cpp"
        "test_strto_unsigned_short.cpp"
        "test_strto_unsigned_int.cpp"
        "test_strto_unsigned_long.cpp"
        "test_strto_unsigned_long_long.cpp"
        "test_strto_int16.cpp"
        "test_strto_int32.cpp"
        "test_strto_int64.cpp"
        "test_strto_uint16.cpp"
        "test_strto_uint32.cpp"
        "test_strto_uint64.cpp")
target_link_libraries(test_utilities_strto PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(test_utilities_strto PRIVATE utilities)
gtest_add_tests(TARGET test_utilities_strto)
