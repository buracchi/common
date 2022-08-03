#include <gtest/gtest.h>

extern "C" {
#include <buracchi/common/utilities/strto.h>
}

#include <string>

TEST(cmn_strto_long, simple_case) {
	long i;
	auto ret = cmn_strto_long(&i, (char *)"11", 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 11);
}

TEST(cmn_strto_long, negative_number) {
	long i;
	auto ret = cmn_strto_long(&i, (char *)"-171", 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == -171);
}

TEST(cmn_strto_long, hexadecimal_base) {
	long i;
	auto ret = cmn_strto_long(&i, (char *)"11", 16);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 0x11);
}

TEST(cmn_strto_long, zero) {
	long i;
	auto ret = cmn_strto_long(&i, (char *)"0", 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 0);
}

TEST(cmn_strto_long, on_LONG_MAX) {
	long i;
	auto str = std::to_string(LONG_MAX);
	auto ret = cmn_strto_long(&i, str.c_str(), 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == LONG_MAX);
}

TEST(cmn_strto_long, on_LONG_MIN) {
	long i;
	auto str = std::to_string(LONG_MIN);
	auto ret = cmn_strto_long(&i, str.c_str(), 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == LONG_MIN);
}

TEST(cmn_strto_long, fail_on_leadingand_space) {
	long i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_long(&i, (char *)" 1", 10));
}

TEST(cmn_strto_long, fail_on_leading_trash_characters) {
	long i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_long(&i, (char *)"a1", 10));
}

TEST(cmn_strto_long, fail_on_trailing_space) {
	long i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_long(&i, (char *)"1 ", 10));
}

TEST(cmn_strto_long, fail_on_trailing_trash_characters) {
	long i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_long(&i, (char *)"1a", 10));
}

TEST(cmn_strto_long, fail_on_overflow) {
	long i;
	auto str = std::to_string(LONG_MAX) + "0";
	ASSERT_EQ(CMN_STRTO_OVERFLOW, cmn_strto_long(&i, str.c_str(), 10));
}

TEST(cmn_strto_long, fail_on_underflow) {
	long i;
	auto str = std::to_string(LONG_MIN) + "0";
	ASSERT_EQ(CMN_STRTO_UNDERFLOW, cmn_strto_long(&i, str.c_str(), 10));
}
