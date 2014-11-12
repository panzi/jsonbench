#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

// usage: jsonbench <repeat> <buffer-size> <json-file>

int jsonbench(const char buffer[], size_t filesize, size_t stride);

int main(int argc, const char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "illegal number of arguments\n");
        return 1;
    }

    char *endptr = NULL;

    unsigned long int repeat = strtoul(argv[1], &endptr, 10);
    if (!*argv[1] || *endptr) {
        fprintf(stderr, "illegal repeat: %s\n", argv[1]);
        return 1;
    }

    unsigned long int buffer_size = strtoul(argv[2], &endptr, 10);
    if (!*argv[2] || *endptr || buffer_size == 0) {
        fprintf(stderr, "illegal buffer size: %s\n", argv[2]);
        return 1;
    }

    const char *filename = argv[3];
    int fd = open(filename, O_RDONLY);

    if (fd < 0) {
        perror(filename);
        return 1;
    }

    struct stat meta;
    if (fstat(fd, &meta) != 0) {
        perror(filename);
        close(fd);
        return 1;
    }

    char *buffer = malloc(meta.st_size);
    if (!buffer) {
        perror("allocating buffer");
        close(fd);
        return 1;
    }

    if (read(fd, buffer, meta.st_size) != meta.st_size) {
        perror(filename);
        free(buffer);
        close(fd);
        return 1;
    }

    unsigned long long duration = 0;
    for (unsigned long int i = 0; i < repeat; ++ i) {
        clock_t start = clock();
        if (jsonbench(buffer, meta.st_size, buffer_size) != 0) {
            fprintf(stderr, "error running jsonbench\n");
            free(buffer);
            close(fd);
            return 1;
        }
        clock_t end = clock();

        if (start == (clock_t)-1 || end == (clock_t)-1) {
            fprintf(stderr, "clock error\n");
            free(buffer);
            close(fd);
            return 1;
        }

        duration += end - start;
    }
    printf("%llu\n", duration / (CLOCKS_PER_SEC / 1000));

    free(buffer);
    close(fd);

    return 0;
}
