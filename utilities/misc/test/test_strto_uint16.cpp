#include <gtest/gtest.h>

extern "C" {
    #include <buracchi/common/utilities/strto.h>
}

TEST(cmn_strto_uint16, simple_case) {
    uint16_t i;
    ASSERT_EQ((cmn_strto_uint16(&i, (char*)"11", 10) == 0) && (i == 11), true);
}

TEST(cmn_strto_uint16, hexadecimal_base) {
    uint16_t i;
    ASSERT_EQ((cmn_strto_uint16(&i, (char*)"11", 16) == 0) && (i == 17), true);
}

TEST(cmn_strto_uint16, zero) {
    uint16_t i;
    ASSERT_EQ((cmn_strto_uint16(&i, (char*)"0", 10) == 0) && (i == 0), true);
}

TEST(cmn_strto_uint16, on_UINT16_MAX) {
    uint16_t i;
    ASSERT_EQ((cmn_strto_uint16(&i, (char*)"65535", 10) == 0) && (i == UINT16_MAX), true);
}

TEST(cmn_strto_uint16, leadingand_space) {
    uint16_t i;
    ASSERT_EQ(cmn_strto_uint16(&i, (char*)" 1", 10) == 0, false);
}

TEST(cmn_strto_uint16, leading_trash_characters) {
    uint16_t i;
    ASSERT_EQ(cmn_strto_uint16(&i, (char*)"a1", 10) == 0, false);
}

TEST(cmn_strto_uint16, trailing_space) {
    uint16_t i;
    ASSERT_EQ(cmn_strto_uint16(&i, (char*)"1 ", 10) == 0, false);
}

TEST(cmn_strto_uint16, trailing_trash_characters) {
    uint16_t i;
    ASSERT_EQ(cmn_strto_uint16(&i, (char*)"1a", 10) == 0, false);
}

TEST(cmn_strto_uint16, overflow) {
    uint16_t i;
    ASSERT_EQ(cmn_strto_uint16(&i, (char*)"65536", 10) == 0, false);
}

TEST(cmn_strto_uint16, underflow) {
    uint16_t i;
    ASSERT_EQ(cmn_strto_uint16(&i, (char*)"-1", 10) == 0, false);
}
