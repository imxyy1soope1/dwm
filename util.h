/* See LICENSE file for copyright and license details. */

#include <stddef.h>

#include "config.h"

#define MAX(A, B)               ((A) > (B) ? (A) : (B))
#define MIN(A, B)               ((A) < (B) ? (A) : (B))
#define BETWEEN(X, A, B)        ((A) <= (X) && (X) <= (B))

#if LOG_LEVEL == LOG_LEVEL_DEBUG
#   ifdef LOG_FILE
#       define DEBUG(...) fprintf(LOG_FILE, "[DEBUG] " __VA_ARGS__)
#   else
#       define DEBUG(...) fprintf(stderr, "[DEBUG] " __VA_ARGS__)
#   endif
#else
#   define DEBUG(...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_INFO
#   ifdef LOG_FILE
#       define INFO(...) fprintf(LOG_FILE, "[INFO] " __VA_ARGS__)
#   else
#       define INFO(...) fprintf(stderr, "[INFO] " __VA_ARGS__)
#   endif
#else
#   define INFO(...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_WARNING
#   ifdef LOG_FILE
#       define WARNING(...) fprintf(LOG_FILE, "[WARNING] " __VA_ARGS__)
#   else
#       define WARNING(...) fprintf(stderr, "[WARNING] " __VA_ARGS__)
#   endif
#else
#   define WARNING(...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_ERROR
#   ifdef LOG_FILE
#       define ERROR(...) fprintf(LOG_FILE, "[ERROR] " __VA_ARGS__)
#   else
#       define ERROR(...) fprintf(stderr, "[ERROR] " __VA_ARGS__)
#   endif
#else
#   define ERROR(...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_CRITICAL
#   ifdef LOG_FILE
#       define CRITICAL(...) fprintf(LOG_FILE, "[CRITICAL] " __VA_ARGS__)
#   else
#       define CRITICAL(...) fprintf(stderr, "[CRITICAL]" __VA_ARGS__)
#   endif
#else
#   define CRITICAL(...)
#endif

void die(const char *fmt, ...);
void *ecalloc(size_t nmemb, size_t size);
int normalizepath(const char *path, char **normal);
int mkdirp(const char *path);
int parentdir(const char *path, char **parent);
int nullterminate(char **str, size_t *len);
