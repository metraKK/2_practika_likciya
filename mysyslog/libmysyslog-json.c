
#include "mysyslog_json.h"
#include <stdio.h>
#include <time.h>

int mysyslog_json(const char* msg, int level, const char* path)
{
    FILE* file = fopen(path, "a");
    if (!file) return -1;

    time_t now = time(NULL);
    fprintf(file, "{\"timestamp\":%ld,\"log_level\":%d,\"message\":\"%s\"}\n", now, level, msg);
    fclose(file);
    return 0;
}
