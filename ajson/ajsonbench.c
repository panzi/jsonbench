#include <ajson.h>

int jsonbench(const char buffer[], size_t filesize, size_t stride) {
    ajson_parser parser;
    if (ajson_init(&parser, FLAGS, AJSON_ENC_UTF8) != 0) {
        return -1;
    }

    size_t index = 0;
    bool atend = false;
    while (!atend) {
        if (index < filesize) {
            size_t size = index + stride > filesize ? filesize - index : stride;

            if (ajson_feed(&parser, buffer + index, size) != 0) {
                ajson_destroy(&parser);
                return -1;
            }
            index += size;
        }
        else {
            if (ajson_feed(&parser, NULL, 0) != 0) {
                ajson_destroy(&parser);
                return -1;
            }
        }

        bool has_tokens = true;
        while (has_tokens) {
            enum ajson_token token = ajson_next_token(&parser);

            switch (token) {
            case AJSON_TOK_NEED_DATA:
                has_tokens = false;
                break;

            case AJSON_TOK_END:
                has_tokens = false;
                atend = true;
                break;

            case AJSON_TOK_ERROR:
            {
                size_t errorpos = index + parser.input_current;
                size_t lineno = 1;
                size_t column = 1;
                for (const char *ptr = buffer, *endptr = buffer + errorpos; ptr != endptr; ++ ptr) {
                    if (*ptr == '\n') {
                        lineno ++;
                        column = 1;
                    }
                    else {
                        column ++;
                    }
                }

                fprintf(stderr, "error at lineno %lu and column %lu (offset %lu): %s\n", lineno, column, errorpos, ajson_error_str(parser.value.error.error));
                fprintf(stderr, "%s:%zu: %s: error raised here\n",
                        parser.value.error.filename,
                        parser.value.error.lineno,
                        parser.value.error.function);
                ajson_destroy(&parser);
                return -1;
            }
            default:
                break;
            }
        }
    }

    ajson_destroy(&parser);
    return 0;
}
