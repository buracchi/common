#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>

enum cmn_logger_log_level {
	CMN_LOGGER_LOG_LEVEL_OFF = 0,           // No events will be logged.
	CMN_LOGGER_LOG_LEVEL_FATAL = 1,         // A fatal event that will prevent the application from continuing.
	CMN_LOGGER_LOG_LEVEL_ERROR = 2,         // An error in the application, possibly recoverable.
	CMN_LOGGER_LOG_LEVEL_WARN = 3,          // An event that might possible lead to an error.
	CMN_LOGGER_LOG_LEVEL_INFO = 4,          // An event for informational purposes.
	CMN_LOGGER_LOG_LEVEL_DEBUG = 5,         // A general debugging event.
	CMN_LOGGER_LOG_LEVEL_TRACE = 6,         // A fine-grained debug message, typically capturing the flow through the application.
	CMN_LOGGER_LOG_LEVEL_ALL = INT_MAX      // All events should be logged.
};

#define cmn_logger_log_trace(...) cmn_logger_log(CMN_LOGGER_LOG_LEVEL_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define cmn_logger_log_debug(...) cmn_logger_log(CMN_LOGGER_LOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define cmn_logger_log_info(...)  cmn_logger_log(CMN_LOGGER_LOG_LEVEL_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define cmn_logger_log_warn(...)  cmn_logger_log(CMN_LOGGER_LOG_LEVEL_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define cmn_logger_log_error(...) cmn_logger_log(CMN_LOGGER_LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define cmn_logger_log_fatal(...) cmn_logger_log(CMN_LOGGER_LOG_LEVEL_FATAL, __FILE__, __LINE__, __VA_ARGS__)

extern void cmn_logger_set_default_level(enum cmn_logger_log_level level);
extern void cmn_logger_set_file(FILE* file);
extern void cmn_logger_show_date_time(bool show_date_time);
extern void cmn_logger_show_source_file(bool show_source_file);
extern void cmn_logger_show_process_id(bool show_process_id);
extern void cmn_logger_show_thread_id(bool show_thread_id);
extern void cmn_logger_show_level_name(bool show_level_name);

extern void cmn_logger_log(enum cmn_logger_log_level level, const char* file, int line, const char* fmt, ...);
