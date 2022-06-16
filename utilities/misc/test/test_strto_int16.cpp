#include <gtest/gtest.h>

extern "C" {
    #include <buracchi/common/utilities/strto.h>
}

TEST(cmn_strto_int16, simple_case) {
    int16_t i;
    ASSERT_EQ((cmn_strto_int16(&i, (char*)"11", 10) == 0) && (i == 11), true);
}

TEST(cmn_strto_int16, negative_number) {
    int16_t i;
    ASSERT_EQ((cmn_strto_int16(&i, (char*)"-11", 10) == 0) && (i == -11), true);
}

TEST(cmn_strto_int16, hexadecimal_base) {
    int16_t i;
    ASSERT_EQ((cmn_strto_int16(&i, (char*)"11", 16) == 0) && (i == 17), true);
}

TEST(cmn_strto_int16, zero) {
    int16_t i;
    ASSERT_EQ((cmn_strto_int16(&i, (char*)"0", 10) == 0) && (i == 0), true);
}

TEST(cmn_strto_int16, on_INT16_MAX) {
    int16_t i;
    ASSERT_EQ((cmn_strto_int16(&i, (char*)"32767", 10) == 0) && (i == INT16_MAX), true);
}

TEST(cmn_strto_int16, on_INT16_MIN) {
    int16_t i;
    ASSERT_EQ((cmn_strto_int16(&i, (char*)"-32768", 10) == 0) && (i == INT16_MIN), true);
}

TEST(cmn_strto_int16, leadingand_space) {
    int16_t i;
    ASSERT_EQ(cmn_strto_int16(&i, (char*)" 1", 10) == 0, false);
}

TEST(cmn_strto_int16, leading_trash_characters) {
    int16_t i;
    ASSERT_EQ(cmn_strto_int16(&i, (char*)"a1", 10) == 0, false);
}

TEST(cmn_strto_int16, trailing_space) {
    int16_t i;
    ASSERT_EQ(cmn_strto_int16(&i, (char*)"1 ", 10) == 0, false);
}

TEST(cmn_strto_int16, trailing_trash_characters) {
    int16_t i;
    ASSERT_EQ(cmn_strto_int16(&i, (char*)"1a", 10) == 0, false);
}

TEST(cmn_strto_int16, overflow) {
    int16_t i;
    ASSERT_EQ(cmn_strto_int16(&i, (char*)"32768", 10) == 0, false);
}

TEST(cmn_strto_int16, underflow) {
    int16_t i;
    ASSERT_EQ(cmn_strto_int16(&i, (char*)"-32769", 10) == 0, false);
}
