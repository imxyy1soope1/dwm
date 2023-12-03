/* See LICENSE file for copyright and license details. */

#ifndef UTIL_H_
#define UTIL_H_

#include <stddef.h>
#include <bits/types/FILE.h>

#define MAX(A, B)               ((A) > (B) ? (A) : (B))
#define MIN(A, B)               ((A) < (B) ? (A) : (B))
#define BETWEEN(X, A, B)        ((A) <= (X) && (X) <= (B))

/* logging */
#define LOG_LEVEL_DEBUG   0
#define LOG_LEVEL_INFO    1
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_ERROR   3
#define LOG_LEVEL_FATAL   4
#define LOG_LEVEL_NOLOG   5

extern FILE *_log;
#define LOG_LEVEL LOG_LEVEL_DEBUG
#define LOG_FILE _log
#define LOG_FILEPATH "/tmp/dwm.log"

#if LOG_LEVEL == LOG_LEVEL_DEBUG
#   ifdef LOG_FILE
#       define DEBUG(...) {fprintf(LOG_FILE, "[DEBUG] " __VA_ARGS__); fprintf(stdout, "[DEBUG] "  __VA_ARGS__);}
#       define DEBUG_NOFMT(...) {fprintf(LOG_FILE, __VA_ARGS__); fprintf(stdout, __VA_ARGS__);}
#   else
#       define DEBUG(...) fprintf(stderr, "[DEBUG] " __VA_ARGS__)
#       define DEBUG_NOFMT(...) fprintf(stdout, __VA_ARGS__)
#   endif
#else
#   define DEBUG(...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_INFO
#   ifdef LOG_FILE
#       define INFO(...) {fprintf(LOG_FILE, "[INFO] " __VA_ARGS__); fprintf(stdout, "[INFO] " __VA_ARGS__);}
#       define INFO_NOFMT(...) {fprintf(LOG_FILE, __VA_ARGS__); fprintf(stdout, __VA_ARGS__);}
#   else
#       define INFO(...) fprintf(stderr, "[INFO] " __VA_ARGS__)
#       define INFO_NOFMT(...) fprintf(stdout, __VA_ARGS__)
#   endif
#else
#   define INFO(...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_WARNING
#   ifdef LOG_FILE
#       define WARNING(...) {fprintf(LOG_FILE, "[WARNING] " __VA_ARGS__); fprintf(stderr, "[WARNING] " __VA_ARGS__);}
#       define WARNING_NOFMT(...) {fprintf(LOG_FILE, __VA_ARGS__); fprintf(stderr, __VA_ARGS__);}
#   else
#       define WARNING(...) fprintf(stderr, "[WARNING] " __VA_ARGS__)
#       define WARNING_NOFMT(...) fprintf(stderr, __VA_ARGS__)
#   endif
#else
#   define WARNING(...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_ERROR
#   ifdef LOG_FILE
#       define ERROR(...) {fprintf(LOG_FILE, "[ERROR] " __VA_ARGS__); fprintf(stderr, "[ERROR] " __VA_ARGS__);}
#       define ERROR_NOFMT(...) {fprintf(LOG_FILE, __VA_ARGS__); fprintf(stderr, __VA_ARGS__);}
#   else
#       define ERROR(...) fprintf(stderr, "[ERROR] " __VA_ARGS__)
#       define ERROR_NOFMT(...) fprintf(stderr, __VA_ARGS__)
#   endif
#else
#   define ERROR(...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_FATAL
#   ifdef LOG_FILE
#       define FATAL(...) {fprintf(LOG_FILE, "[FATAL] " __VA_ARGS__); fprintf(stderr, "[FATAL] " __VA_ARGS__);}
#       define FATAL_NOFMT(...) {fprintf(LOG_FILE, __VA_ARGS__); fprintf(stderr, __VA_ARGS__);}
#   else
#       define FATAL(...) fprintf(stderr, "[FATAL]" __VA_ARGS__)
#       define FATAL_NOFMT(...) fprintf(stderr, __VA_ARGS__)
#   endif
#else
#   define FATAL(...)
#endif

void die(const char *fmt, ...);
void *ecalloc(size_t nmemb, size_t size);
int normalizepath(const char *path, char **normal);
int mkdirp(const char *path);
int parentdir(const char *path, char **parent);
int nullterminate(char **str, size_t *len);

#endif /* UTIL_H_ */
