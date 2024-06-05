#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include <mysyslog.h>

int main(int argc, char **argv) {
    int opt;
    char *message = NULL;
    int level = LOG_INFO;
    char *driver = "stdout";
    char *format = "text";
    char *path = NULL;

    while ((opt = getopt(argc, argv, "m:p:d:f:o:")) != -1) {
        switch (opt) {
            case 'm':
                message = optarg;
                break;
            case 'p':
                level = atoi(optarg);
                break;
            case 'd':
                driver = optarg;
                break;
            case 'f':
                format = optarg;
                break;
            case 'o':
                path = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s -m <message> -p <priority> -d <driver> -f <format> -o <filename>\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (!message) {
        fprintf(stderr, "Error: Missing message argument (-m).\n");
        exit(EXIT_FAILURE);
    }

    if (!driver) {
        fprintf(stderr, "Error: Missing driver argument (-d).\n");
        exit(EXIT_FAILURE);
    }

    if (!format) {
        fprintf(stderr, "Error: Missing format argument (-f).\n");
        exit(EXIT_FAILURE);
    }

    if (!path) {
        path = "stdout";
    }

    int result = mysyslog(message, level, driver, format, path);
    if (result != 0) {
        fprintf(stderr, "Error: Failed to write to syslog.\n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
