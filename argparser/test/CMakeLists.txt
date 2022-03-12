add_library(
        main-mock
        "main-mock.c"
        "main-mock.h"
)
target_link_libraries(main-mock PRIVATE argparser)
target_link_libraries(main-mock INTERFACE coverage_config)

add_executable(
        test_argparser
        "argparser.cpp"
)
target_link_libraries(test_argparser PRIVATE GTest::GTest GTest::Main)
target_link_libraries(test_argparser PRIVATE main-mock)
gtest_add_tests(TARGET test_argparser)
