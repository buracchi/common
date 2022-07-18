#include <gtest/gtest.h>

extern "C" {
#include <buracchi/common/logger/logger.h>
}

TEST(cmn_logger, dummy) {
    cmn_logger_log_fatal("Message");
    cmn_logger_log_error("Message");
    cmn_logger_log_warn("Message");
    cmn_logger_log_info("Message");
    cmn_logger_log_debug("Message");
    cmn_logger_log_trace("Message");
    ASSERT_EQ(true, true);
}
