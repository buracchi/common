#include <buracchi/common/logger/logger.h>

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#ifdef __unix__
#include <unistd.h>
#include <threads.h>
#include <stdatomic.h>
#else
#include <Windows.h>
#include <synchapi.h>
#include <process.h>
enum {
	thrd_success,
	thrd_nomem,
	thrd_timedout,
	thrd_busy,
	thrd_error
};
enum {
	mtx_plain,
	mtx_recursive,
	mtx_timed
};
#define getpid() _getpid()
#define thrd_current() GetCurrentThreadId()
#define atomic_compare_exchange_strong(obj, expected, desired) (InterlockedCompareExchangePointer(obj, desired, *expected) == (*expected))
#define mtx_t HANDLE
#define mtx_init(mutex, type) (((*(mutex)) = CreateMutex(NULL, FALSE, NULL)) ? thrd_success : thrd_error)
#define mtx_lock(mutex) ((WaitForSingleObject(*(mutex), INFINITE) == WAIT_OBJECT_0) ? thrd_success : thrd_error)
#define mtx_unlock(mutex) ((ReleaseMutex(*(mutex))) ? thrd_success : thrd_error)
#define mtx_destroy(mutex) CloseHandle((*(mutex)))
#endif

#include <buracchi/common/utilities/try.h>

struct logger_config {
	enum cmn_logger_log_level default_level;
	FILE* file;
	bool show_date_time;
	bool show_source_file;
	bool show_process_id;
	bool show_thread_id;
	bool show_level_name;
};

static mtx_t mutex;

static struct logger {
	struct logger_config config;
	mtx_t* mutex;
} logger = {
	.mutex = NULL
};

static const char* level_strings[] = {
	[CMN_LOGGER_LOG_LEVEL_FATAL] = "FATAL",
	[CMN_LOGGER_LOG_LEVEL_ERROR] = "ERROR",
	[CMN_LOGGER_LOG_LEVEL_WARN] = "WARN",
	[CMN_LOGGER_LOG_LEVEL_INFO] = "INFO",
	[CMN_LOGGER_LOG_LEVEL_DEBUG] = "DEBUG",
	[CMN_LOGGER_LOG_LEVEL_TRACE] = "TRACE"
};

#ifdef CMN_LOGGER_USE_COLOR

#define RESET_STYLE			"\x1b[0m"

#define COLOR_BLACK			"\x1b[30m"
#define COLOR_RED			"\x1b[31m"
#define COLOR_GREEN			"\x1b[32m"
#define COLOR_YELLOW		"\x1b[33m"
#define COLOR_BLUE			"\x1b[34m"
#define COLOR_MAGENTA		"\x1b[35m"
#define COLOR_CYAN			"\x1b[36m"
#define COLOR_WHITE			"\x1b[37m"

#define COLOR_LIGHT_BLUE	"\x1b[94m"

static const char* level_colors[] = {
	[CMN_LOGGER_LOG_LEVEL_FATAL] = COLOR_MAGENTA,
	[CMN_LOGGER_LOG_LEVEL_ERROR] = COLOR_RED,
	[CMN_LOGGER_LOG_LEVEL_WARN] = COLOR_YELLOW,
	[CMN_LOGGER_LOG_LEVEL_INFO] = COLOR_GREEN,
	[CMN_LOGGER_LOG_LEVEL_DEBUG] = COLOR_CYAN,
	[CMN_LOGGER_LOG_LEVEL_TRACE] = COLOR_LIGHT_BLUE
};
#endif

static inline char* get_date_time(char(*date_time)[20]);

static inline struct logger* get_logger(void) {
	if (logger.mutex != NULL) {
		return &logger;
	}
	mtx_t mtx;
	while (mtx_init(&mtx, mtx_plain) != thrd_success);
	while (mtx_lock(&mtx) != thrd_success);
	if (atomic_compare_exchange_strong(&logger.mutex, &(mtx_t *){ NULL }, &mutex)) {
		memcpy(logger.mutex, &mtx, sizeof(mtx_t));
		logger.config.default_level = CMN_LOGGER_LOG_LEVEL_ALL;
		logger.config.file = stderr;
		logger.config.show_date_time = true;
		logger.config.show_source_file = false;
		logger.config.show_level_name = true;
		logger.config.show_process_id = false;
		logger.config.show_thread_id = false;
		while (mtx_unlock(logger.mutex) != thrd_success);
	}
	else {
		mtx_unlock(&mtx);
		mtx_destroy(&mtx);
		while (mtx_lock(logger.mutex) != thrd_success); // wait termination of logger initialization
		while (mtx_unlock(logger.mutex) != thrd_success);
	}
	return &logger;
}

extern void cmn_logger_set_default_level(enum cmn_logger_log_level level) {
	get_logger()->config.default_level = level;
}

extern void cmn_logger_set_file(FILE* file) {
	get_logger()->config.file = file;
}

extern void cmn_logger_show_date_time(bool show_date_time) {
	get_logger()->config.show_date_time = show_date_time;
}

extern void cmn_logger_show_source_file(bool show_source_file) {
	get_logger()->config.show_source_file = show_source_file;
}

extern void cmn_logger_show_process_id(bool show_process_id) {
	get_logger()->config.show_process_id = show_process_id;
}

extern void cmn_logger_show_thread_id(bool show_thread_id) {
	get_logger()->config.show_thread_id = show_thread_id;
}

extern void cmn_logger_show_level_name(bool show_level_name) {
	get_logger()->config.show_level_name = show_level_name;
}

extern void cmn_logger_log(enum cmn_logger_log_level level, const char* file, int line, const char* fmt, ...) {
	va_list ap;
	get_logger();
	if (level >= 0 && logger.config.default_level >= level) {
		try(mtx_lock(logger.mutex), thrd_error, fail);
		va_start(ap, fmt);
		if (logger.config.show_date_time) {
			fprintf(logger.config.file, "%s ", get_date_time(&(char[20]) { 0 }));
		}
		if (logger.config.show_level_name) {
#ifdef CMN_LOGGER_USE_COLOR
			fprintf(logger->config.file, "%s%-5s" RESET_STYLE " ", level_colors[level], level_strings[level]);
#else
			fprintf(logger.config.file, "%-5s ", level_strings[level]);
#endif
		}
		if (logger.config.show_process_id) {
			fprintf(logger.config.file, "%d ", getpid());
		}
		if (logger.config.show_thread_id) {
			fprintf(logger.config.file, "%lu ", thrd_current());
		}
		if (logger.config.show_source_file) {
			fprintf(logger.config.file, "%s: %d ", file, line);
		}
		fprintf(logger.config.file, "- ");
		vfprintf(logger.config.file, fmt, ap);
		fprintf(logger.config.file, "\n");
		while (mtx_unlock(logger.mutex) != thrd_success);
		fflush(logger.config.file);
		va_end(ap);
	}
fail:
	return;
}

static inline char* get_date_time(char(*date_time)[20]) {
	time_t t = time(NULL);
	struct tm* tm = localtime(&t);
	strftime(*date_time, sizeof * date_time, "%F %T", tm);
	return *date_time;
}
