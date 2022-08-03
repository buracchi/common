#include <gtest/gtest.h>

extern "C" {
#include <buracchi/common/utilities/strto.h>
}

#include <string>

TEST(cmn_strto_unsigned_int, simple_case) {
	unsigned int i;
	auto ret = cmn_strto_unsigned_int(&i, (char *)"11", 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 11);
}

TEST(cmn_strto_unsigned_int, hexadecimal_base) {
	unsigned int i;
	auto ret = cmn_strto_unsigned_int(&i, (char *)"11", 16);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 0x11);
}

TEST(cmn_strto_unsigned_int, zero) {
	unsigned int i;
	auto ret = cmn_strto_unsigned_int(&i, (char *)"0", 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 0);
}

TEST(cmn_strto_unsigned_int, on_UINT_MAX) {
	unsigned int i;
	auto str = std::to_string(UINT_MAX);
	auto ret = cmn_strto_unsigned_int(&i, str.c_str(), 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == UINT_MAX);
}

TEST(cmn_strto_unsigned_int, fail_on_leadingand_space) {
	unsigned int i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_unsigned_int(&i, (char *)" 1", 10));
}

TEST(cmn_strto_unsigned_int, fail_on_leading_trash_characters) {
	unsigned int i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_unsigned_int(&i, (char *)"a1", 10));
}

TEST(cmn_strto_unsigned_int, fail_on_trailing_space) {
	unsigned int i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_unsigned_int(&i, (char *)"1 ", 10));
}

TEST(cmn_strto_unsigned_int, fail_on_trailing_trash_characters) {
	unsigned int i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_unsigned_int(&i, (char *)"1a", 10));
}

TEST(cmn_strto_unsigned_int, fail_on_overflow) {
	unsigned int i;
	auto str = std::to_string(UINT_MAX) + "0";
	ASSERT_EQ(CMN_STRTO_OVERFLOW, cmn_strto_unsigned_int(&i, str.c_str(), 10));
}

TEST(cmn_strto_unsigned_int, fail_on_underflow) {
	unsigned int i;
	auto str = std::to_string(-1);
	ASSERT_EQ(CMN_STRTO_UNDERFLOW, cmn_strto_unsigned_int(&i, str.c_str(), 10));
}
