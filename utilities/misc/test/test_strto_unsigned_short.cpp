#include <gtest/gtest.h>

extern "C" {
#include <buracchi/common/utilities/strto.h>
}

#include <string>

TEST(cmn_strto_unsigned_short, simple_case) {
	unsigned short i;
	auto ret = cmn_strto_unsigned_short(&i, (char *)"11", 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 11);
}

TEST(cmn_strto_unsigned_short, hexadecimal_base) {
	unsigned short i;
	auto ret = cmn_strto_unsigned_short(&i, (char *)"11", 16);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 0x11);
}

TEST(cmn_strto_unsigned_short, zero) {
	unsigned short i;
	auto ret = cmn_strto_unsigned_short(&i, (char *)"0", 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 0);
}

TEST(cmn_strto_unsigned_short, on_USHRT_MAX) {
	unsigned short i;
	auto str = std::to_string(USHRT_MAX);
	auto ret = cmn_strto_unsigned_short(&i, str.c_str(), 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == USHRT_MAX);
}

TEST(cmn_strto_unsigned_short, fail_on_leadingand_space) {
	unsigned short i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_unsigned_short(&i, (char *)" 1", 10));
}

TEST(cmn_strto_unsigned_short, fail_on_leading_trash_characters) {
	unsigned short i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_unsigned_short(&i, (char *)"a1", 10));
}

TEST(cmn_strto_unsigned_short, fail_on_trailing_space) {
	unsigned short i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_unsigned_short(&i, (char *)"1 ", 10));
}

TEST(cmn_strto_unsigned_short, fail_on_trailing_trash_characters) {
	unsigned short i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_unsigned_short(&i, (char *)"1a", 10));
}

TEST(cmn_strto_unsigned_short, fail_on_overflow) {
	unsigned short i;
	auto str = std::to_string(USHRT_MAX) + "0";
	ASSERT_EQ(CMN_STRTO_OVERFLOW, cmn_strto_unsigned_short(&i, str.c_str(), 10));
}

TEST(cmn_strto_unsigned_short, fail_on_underflow) {
	unsigned short i;
	auto str = std::to_string(-1);
	ASSERT_EQ(CMN_STRTO_UNDERFLOW, cmn_strto_unsigned_short(&i, str.c_str(), 10));
}
