#include <gtest/gtest.h>

extern "C" {
    #include <buracchi/common/utilities/strto.h>
}

TEST(cmn_strto_uint32, simple_case) {
    uint32_t i;
    ASSERT_EQ((cmn_strto_uint32(&i, (char*)"11", 10) == 0) && (i == 11), true);
}

TEST(cmn_strto_uint32, hexadecimal_base) {
    uint32_t i;
    ASSERT_EQ((cmn_strto_uint32(&i, (char*)"11", 16) == 0) && (i == 17), true);
}

TEST(cmn_strto_uint32, zero) {
    uint32_t i;
    ASSERT_EQ((cmn_strto_uint32(&i, (char*)"0", 10) == 0) && (i == 0), true);
}

TEST(cmn_strto_uint32, on_UINT32_MAX) {
    uint32_t i;
    ASSERT_EQ((cmn_strto_uint32(&i, (char*)"4294967295", 10) == 0) && (i == UINT32_MAX), true);
}

TEST(cmn_strto_uint32, leadingand_space) {
    uint32_t i;
    ASSERT_EQ(cmn_strto_uint32(&i, (char*)" 1", 10) == 0, false);
}

TEST(cmn_strto_uint32, leading_trash_characters) {
    uint32_t i;
    ASSERT_EQ(cmn_strto_uint32(&i, (char*)"a1", 10) == 0, false);
}

TEST(cmn_strto_uint32, trailing_space) {
    uint32_t i;
    ASSERT_EQ(cmn_strto_uint32(&i, (char*)"1 ", 10) == 0, false);
}

TEST(cmn_strto_uint32, trailing_trash_characters) {
    uint32_t i;
    ASSERT_EQ(cmn_strto_uint32(&i, (char*)"1a", 10) == 0, false);
}

TEST(cmn_strto_uint32, overflow) {
    uint32_t i;
    ASSERT_EQ(cmn_strto_uint32(&i, (char*)"4294967296", 10) == 0, false);
}

TEST(cmn_strto_uint32, underflow) {
    uint32_t i;
    ASSERT_EQ(cmn_strto_uint32(&i, (char*)"-1", 10) == 0, false);
}
