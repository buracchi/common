#include <gtest/gtest.h>

extern "C" {
#include <buracchi/common/utilities/strto.h>
}

#include <string>

TEST(cmn_strto_unsigned_long_long, simple_case) {
	unsigned long long i;
	auto ret = cmn_strto_unsigned_long_long(&i, (char *)"11", 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 11);
}

TEST(cmn_strto_unsigned_long_long, hexadecimal_base) {
	unsigned long long i;
	auto ret = cmn_strto_unsigned_long_long(&i, (char *)"11", 16);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 0x11);
}

TEST(cmn_strto_unsigned_long_long, zero) {
	unsigned long long i;
	auto ret = cmn_strto_unsigned_long_long(&i, (char *)"0", 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == 0);
}

TEST(cmn_strto_unsigned_long_long, on_ULLONG_MAX) {
	unsigned long long i;
	auto str = std::to_string(ULLONG_MAX);
	auto ret = cmn_strto_unsigned_long_long(&i, str.c_str(), 10);
	ASSERT_TRUE(ret == CMN_STRTO_SUCCESS && i == ULLONG_MAX);
}

TEST(cmn_strto_unsigned_long_long, fail_on_leadingand_space) {
	unsigned long long i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_unsigned_long_long(&i, (char *)" 1", 10));
}

TEST(cmn_strto_unsigned_long_long, fail_on_leading_trash_characters) {
	unsigned long long i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_unsigned_long_long(&i, (char *)"a1", 10));
}

TEST(cmn_strto_unsigned_long_long, fail_on_trailing_space) {
	unsigned long long i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_unsigned_long_long(&i, (char *)"1 ", 10));
}

TEST(cmn_strto_unsigned_long_long, fail_on_trailing_trash_characters) {
	unsigned long long i;
	ASSERT_EQ(CMN_STRTO_INCONVERTIBLE, cmn_strto_unsigned_long_long(&i, (char *)"1a", 10));
}

TEST(cmn_strto_unsigned_long_long, fail_on_overflow) {
	unsigned long long i;
	auto str = std::to_string(ULLONG_MAX) + "0";
	ASSERT_EQ(CMN_STRTO_OVERFLOW, cmn_strto_unsigned_long_long(&i, str.c_str(), 10));
}

TEST(cmn_strto_unsigned_long_long, fail_on_underflow) {
	unsigned long long i;
	auto str = std::to_string(-1);
	ASSERT_EQ(CMN_STRTO_UNDERFLOW, cmn_strto_unsigned_long_long(&i, str.c_str(), 10));
}
