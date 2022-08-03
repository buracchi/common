#include <gtest/gtest.h>

extern "C" {
#include <buracchi/common/utilities/strto.h>
}

#include <string>

TEST(cmn_strto_int, simple_case) {
	int i;
	auto ret = cmn_strto_int(&i, (char *)"11", 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 11);
}

TEST(cmn_strto_int, negative_number) {
	int i;
	auto ret = cmn_strto_int(&i, (char *)"-171", 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == -171);
}

TEST(cmn_strto_int, hexadecimal_base) {
	int i;
	auto ret = cmn_strto_int(&i, (char *)"11", 16);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 0x11);
}

TEST(cmn_strto_int, zero) {
	int i;
	auto ret = cmn_strto_int(&i, (char *)"0", 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 0);
}

TEST(cmn_strto_int, on_INT_MAX) {
	int i;
	auto str = std::to_string(INT_MAX);
	auto ret = cmn_strto_int(&i, str.c_str(), 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == INT_MAX);
}

TEST(cmn_strto_int, on_INT_MIN) {
	int i;
	auto str = std::to_string(INT_MIN);
	auto ret = cmn_strto_int(&i, str.c_str(), 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == INT_MIN);
}

TEST(cmn_strto_int, fail_on_leadingand_space) {
	int i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_int(&i, (char *)" 1", 10));
}

TEST(cmn_strto_int, fail_on_leading_trash_characters) {
	int i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_int(&i, (char *)"a1", 10));
}

TEST(cmn_strto_int, fail_on_trailing_space) {
	int i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_int(&i, (char *)"1 ", 10));
}

TEST(cmn_strto_int, fail_on_trailing_trash_characters) {
	int i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_int(&i, (char *)"1a", 10));
}

TEST(cmn_strto_int, fail_on_overflow) {
	int i;
	auto str = std::to_string(INT_MAX) + "0";
	ASSERT_EQ(CMN_STRTO_OVERFLOW, cmn_strto_int(&i, str.c_str(), 10));
}

TEST(cmn_strto_int, fail_on_underflow) {
	int i;
	auto str = std::to_string(INT_MIN) + "0";
	ASSERT_EQ(CMN_STRTO_UNDERFLOW, cmn_strto_int(&i, str.c_str(), 10));
}
