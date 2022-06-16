#include <gtest/gtest.h>

extern "C" {
    #include <buracchi/common/utilities/strto.h>
}

TEST(cmn_strto_uint64, simple_case) {
    uint64_t i;
    ASSERT_EQ((cmn_strto_uint64(&i, (char*)"11", 10) == 0) && (i == 11), true);
}

TEST(cmn_strto_uint64, hexadecimal_base) {
    uint64_t i;
    ASSERT_EQ((cmn_strto_uint64(&i, (char*)"11", 16) == 0) && (i == 17), true);
}

TEST(cmn_strto_uint64, zero) {
    uint64_t i;
    ASSERT_EQ((cmn_strto_uint64(&i, (char*)"0", 10) == 0) && (i == 0), true);
}

TEST(cmn_strto_uint64, on_UINT64_MAX) {
    uint64_t i;
    ASSERT_EQ((cmn_strto_uint64(&i, (char*)"18446744073709551615", 10) == 0) && (i == UINT64_MAX), true);
}

TEST(cmn_strto_uint64, leadingand_space) {
    uint64_t i;
    ASSERT_EQ(cmn_strto_uint64(&i, (char*)" 1", 10) == 0, false);
}

TEST(cmn_strto_uint64, leading_trash_characters) {
    uint64_t i;
    ASSERT_EQ(cmn_strto_uint64(&i, (char*)"a1", 10) == 0, false);
}

TEST(cmn_strto_uint64, trailing_space) {
    uint64_t i;
    ASSERT_EQ(cmn_strto_uint64(&i, (char*)"1 ", 10) == 0, false);
}

TEST(cmn_strto_uint64, trailing_trash_characters) {
    uint64_t i;
    ASSERT_EQ(cmn_strto_uint64(&i, (char*)"1a", 10) == 0, false);
}

TEST(cmn_strto_uint64, overflow) {
    uint64_t i;
    ASSERT_EQ(cmn_strto_uint64(&i, (char*)"18446744073709551616", 10) == 0, false);
}

TEST(cmn_strto_uint64, underflow) {
    uint64_t i;
    ASSERT_EQ(cmn_strto_uint64(&i, (char*)"-1", 10) == 0, false);
}
