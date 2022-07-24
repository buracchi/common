#include <gtest/gtest.h>

extern "C" {
#include "main-mock.h"
}

TEST(cmn_argparser, test) {
	int argc = 4;
	const char* argv[] = { "./test_program", "test", "-f", "11", nullptr };
	ASSERT_EQ(argv[1], mock_main(argc, argv));
}
