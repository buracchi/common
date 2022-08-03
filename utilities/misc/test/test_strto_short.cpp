#include <gtest/gtest.h>

extern "C" {
#include <buracchi/common/utilities/strto.h>
}

#include <string>

TEST(cmn_strto_short, simple_case) {
	short i;
	auto ret = cmn_strto_short(&i, (char *)"11", 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 11);
}

TEST(cmn_strto_short, negative_number) {
	short i;
	auto ret = cmn_strto_short(&i, (char *)"-171", 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == -171);
}

TEST(cmn_strto_short, hexadecimal_base) {
	short i;
	auto ret = cmn_strto_short(&i, (char *)"11", 16);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 0x11);
}

TEST(cmn_strto_short, zero) {
	short i;
	auto ret = cmn_strto_short(&i, (char *)"0", 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 0);
}

TEST(cmn_strto_short, on_SHRT_MAX) {
	short i;
	auto str = std::to_string(SHRT_MAX);
	auto ret = cmn_strto_short(&i, str.c_str(), 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == SHRT_MAX);
}

TEST(cmn_strto_short, on_SHRT_MIN) {
	short i;
	auto str = std::to_string(SHRT_MIN);
	auto ret = cmn_strto_short(&i, str.c_str(), 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == SHRT_MIN);
}

TEST(cmn_strto_short, fail_on_leadingand_space) {
	short i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_short(&i, (char *)" 1", 10));
}

TEST(cmn_strto_short, fail_on_leading_trash_characters) {
	short i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_short(&i, (char *)"a1", 10));
}

TEST(cmn_strto_short, fail_on_trailing_space) {
	short i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_short(&i, (char *)"1 ", 10));
}

TEST(cmn_strto_short, fail_on_trailing_trash_characters) {
	short i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_short(&i, (char *)"1a", 10));
}

TEST(cmn_strto_short, fail_on_overflow) {
	short i;
	auto str = std::to_string(SHRT_MAX) + "0";
	ASSERT_EQ(CMN_STRTO_OVERFLOW, cmn_strto_short(&i, str.c_str(), 10));
}

TEST(cmn_strto_short, fail_on_underflow) {
	short i;
	auto str = std::to_string(SHRT_MIN) + "0";
	ASSERT_EQ(CMN_STRTO_UNDERFLOW, cmn_strto_short(&i, str.c_str(), 10));
}
