#include <gtest/gtest.h>

extern "C" {
    #include <buracchi/common/utilities/strto.h>
}

TEST(cmn_strto_int64, simple_case) {
    int64_t i;
    ASSERT_EQ((cmn_strto_int64(&i, (char*)"11", 10) == 0) && (i == 11), true);
}

TEST(cmn_strto_int64, negative_number) {
    int64_t i;
    ASSERT_EQ((cmn_strto_int64(&i, (char*)"-11", 10) == 0) && (i == -11), true);
}

TEST(cmn_strto_int64, hexadecimal_base) {
    int64_t i;
    ASSERT_EQ((cmn_strto_int64(&i, (char*)"11", 16) == 0) && (i == 17), true);
}

TEST(cmn_strto_int64, zero) {
    int64_t i;
    ASSERT_EQ((cmn_strto_int64(&i, (char*)"0", 10) == 0) && (i == 0), true);
}

TEST(cmn_strto_int64, on_INT64_MAX) {
    int64_t i;
    ASSERT_EQ((cmn_strto_int64(&i, (char*)"9223372036854775807", 10) == 0) && (i == INT64_MAX), true);
}

TEST(cmn_strto_int64, on_INT64_MIN) {
    int64_t i;
    ASSERT_EQ((cmn_strto_int64(&i, (char*)"-9223372036854775808", 10) == 0) && (i == INT64_MIN), true);
}

TEST(cmn_strto_int64, leadingand_space) {
    int64_t i;
    ASSERT_EQ(cmn_strto_int64(&i, (char*)" 1", 10) == 0, false);
}

TEST(cmn_strto_int64, leading_trash_characters) {
    int64_t i;
    ASSERT_EQ(cmn_strto_int64(&i, (char*)"a1", 10) == 0, false);
}

TEST(cmn_strto_int64, trailing_space) {
    int64_t i;
    ASSERT_EQ(cmn_strto_int64(&i, (char*)"1 ", 10) == 0, false);
}

TEST(cmn_strto_int64, trailing_trash_characters) {
    int64_t i;
    ASSERT_EQ(cmn_strto_int64(&i, (char*)"1a", 10) == 0, false);
}

TEST(cmn_strto_int64, overflow) {
    int64_t i;
    ASSERT_EQ(cmn_strto_int64(&i, (char*)"9223372036854775808", 10) == 0, false);
}

TEST(cmn_strto_int64, underflow) {
    int64_t i;
    ASSERT_EQ(cmn_strto_int64(&i, (char*)"-9223372036854775809", 10) == 0, false);
}
