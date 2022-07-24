#include <gtest/gtest.h>

extern "C" {
#include "main-mock.h"
}

#include <string>

TEST(cmn_argparser, test) {
	int argc = 4;
	const char* argv[] = { "./test_program", "test", "-f", "11", nullptr };
	ASSERT_EQ(std::string(argv[1]), std::string(mock_main(argc, argv)));
}
