#include <gtest/gtest.h>

extern "C" {
#include <buracchi/common/utilities/strto.h>
}

#include <string>

TEST(cmn_strto_unsigned_long, simple_case) {
	unsigned long i;
	auto ret = cmn_strto_unsigned_long(&i, (char *)"11", 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 11);
}

TEST(cmn_strto_unsigned_long, hexadecimal_base) {
	unsigned long i;
	auto ret = cmn_strto_unsigned_long(&i, (char *)"11", 16);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 0x11);
}

TEST(cmn_strto_unsigned_long, zero) {
	unsigned long i;
	auto ret = cmn_strto_unsigned_long(&i, (char *)"0", 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 0);
}

TEST(cmn_strto_unsigned_long, on_ULONG_MAX) {
	unsigned long i;
	auto str = std::to_string(ULONG_MAX);
	auto ret = cmn_strto_unsigned_long(&i, str.c_str(), 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == ULONG_MAX);
}

TEST(cmn_strto_unsigned_long, fail_on_leadingand_space) {
	unsigned long i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_unsigned_long(&i, (char *)" 1", 10));
}

TEST(cmn_strto_unsigned_long, fail_on_leading_trash_characters) {
	unsigned long i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_unsigned_long(&i, (char *)"a1", 10));
}

TEST(cmn_strto_unsigned_long, fail_on_trailing_space) {
	unsigned long i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_unsigned_long(&i, (char *)"1 ", 10));
}

TEST(cmn_strto_unsigned_long, fail_on_trailing_trash_characters) {
	unsigned long i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_unsigned_long(&i, (char *)"1a", 10));
}

TEST(cmn_strto_unsigned_long, fail_on_overflow) {
	unsigned long i;
	auto str = std::to_string(ULONG_MAX) + "0";
	ASSERT_EQ(CMN_STRTO_OVERFLOW, cmn_strto_unsigned_long(&i, str.c_str(), 10));
}

TEST(cmn_strto_unsigned_long, fail_on_underflow) {
	unsigned long i;
	auto str = std::to_string(-1);
	ASSERT_EQ(CMN_STRTO_UNDERFLOW, cmn_strto_unsigned_long(&i, str.c_str(), 10));
}
