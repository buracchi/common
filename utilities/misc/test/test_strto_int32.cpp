#include <gtest/gtest.h>

extern "C" {
    #include <buracchi/common/utilities/strto.h>
}

TEST(cmn_strto_int32, simple_case) {
    int32_t i;
    ASSERT_EQ((cmn_strto_int32(&i, (const char*)"11", 10) == 0) && (i == 11), true);
}

TEST(cmn_strto_int32, negative_number) {
    int32_t i;
    ASSERT_EQ((cmn_strto_int32(&i, (const char*)"-11", 10) == 0) && (i == -11), true);
}

TEST(cmn_strto_int32, hexadecimal_base) {
    int32_t i;
    ASSERT_EQ((cmn_strto_int32(&i, (const char*)"11", 16) == 0) && (i == 17), true);
}

TEST(cmn_strto_int32, zero) {
    int32_t i;
    ASSERT_EQ((cmn_strto_int32(&i, (const char*)"0", 10) == 0) && (i == 0), true);
}

TEST(cmn_strto_int32, on_INT32_MAX) {
    int32_t i;
    ASSERT_EQ((cmn_strto_int32(&i, (const char*)"2147483647", 10) == 0) && (i == INT32_MAX), true);
}

TEST(cmn_strto_int32, on_INT32_MIN) {
    int32_t i;
    ASSERT_EQ((cmn_strto_int32(&i, (const char*)"-2147483648", 10) == 0) && (i == INT32_MIN), true);
}

TEST(cmn_strto_int32, leadingand_space) {
    int32_t i;
    ASSERT_EQ(cmn_strto_int32(&i, (const char*)" 1", 10) == 0, false);
}

TEST(cmn_strto_int32, leading_trash_characters) {
    int32_t i;
    ASSERT_EQ(cmn_strto_int32(&i, (const char*)"a1", 10) == 0, false);
}

TEST(cmn_strto_int32, trailing_space) {
    int32_t i;
    ASSERT_EQ(cmn_strto_int32(&i, (const char*)"1 ", 10) == 0, false);
}

TEST(cmn_strto_int32, trailing_trash_characters) {
    int32_t i;
    ASSERT_EQ(cmn_strto_int32(&i, (const char*)"1a", 10) == 0, false);
}

TEST(cmn_strto_int32, overflow) {
    int32_t i;
    ASSERT_EQ(cmn_strto_int32(&i, (const char*)"2147483648", 10) == 0, false);
}

TEST(cmn_strto_int32, underflow) {
    int32_t i;
    ASSERT_EQ(cmn_strto_int32(&i, (const char*)"-2147483649", 10) == 0, false);
}
