#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <dlfcn.h>
#include "mysyslog.h"

void print_usage() {
    printf("Usage: mysyslog-client -m <message> -l <level> -d <driver> -f <format> -p <path>\n");
}

int main(int argc, char *argv[]) {
    int opt;
    char *message = NULL;
    int level = INFO;
    int driver = 0; // 0 for text, 1 for json
    int format = 0;
    char *path = "log.txt";

    while ((opt = getopt(argc, argv, "m:l:d:f:p:")) != -1) {
        switch (opt) {
            case 'm':
                message = optarg;
                break;
            case 'l':
                level = atoi(optarg);
                break;
            case 'd':
                driver = atoi(optarg);
                break;
            case 'f':
                format = atoi(optarg);
                break;
            case 'p':
                path = optarg;
                break;
            default:
                print_usage();
                return EXIT_FAILURE;
        }
    }

    if (!message) {
        print_usage();
        return EXIT_FAILURE;
    }

    int (*mysyslog_func)(const char*, int, int, int, const char*);
    void *handle = dlopen(driver == 0 ? "libmysyslog_text.so" : "libmysyslog_json.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Failed to load driver: %s\n", dlerror());
        return EXIT_FAILURE;
    }

    *(void **)(&mysyslog_func) = dlsym(handle, "mysyslog");
    if (!mysyslog_func) {
        fprintf(stderr, "Failed to find symbol: %s\n", dlerror());
        return EXIT_FAILURE;
    }

    mysyslog_func(message, level, driver, format, path);
    dlclose(handle);

    return EXIT_SUCCESS;
}
