
#include "mysyslog_text.h"
#include <stdio.h>
#include <time.h>

int mysyslog_text(const char* msg, int level, const char* path) {
    FILE* file = fopen(path, "a");
    if (!file) return -1;

    time_t now = time(NULL);
    fprintf(file, "%ld %d %s\n", now, level, msg);
    fclose(file);
    return 0;
}
