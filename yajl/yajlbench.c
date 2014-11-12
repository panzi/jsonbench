#include <stdlib.h>
#include <yajl/yajl_parse.h>

int jsonbench(const char buffer[], size_t filesize, size_t stride) {
    yajl_handle parser = yajl_alloc(NULL, NULL, NULL);
    yajl_status stat = yajl_status_ok;

    if (!parser) {
        return -1;
    }

    if (!yajl_config(parser, yajl_dont_validate_strings, 0)) {
        yajl_free(parser);
        return -1;
    }

    for (size_t index = 0; index < filesize;) {
        size_t size = index + stride > filesize ? filesize - index : stride;

        stat = yajl_parse(parser, (const unsigned char*)buffer + index, size);
        index += size;
    }

    if (stat == yajl_status_ok) {
        stat = yajl_complete_parse(parser);
    }

    if (stat != yajl_status_ok) {
        yajl_free(parser);
        return -1;
    }

    yajl_free(parser);
    return 0;
}
