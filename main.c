#include <stdlib.h>
#include <string.h>

#include <common/logging.h>

#include "transcode.h"

static const char ENCODE_FLAG[] = "--encode";
static const char DECODE_FLAG[] = "--decode";

void print_usage(const char* argv0) {
    LOG_MSG(info, "Usage: %s [%s | %s] [input file] [output file]\n", argv0, ENCODE_FLAG, DECODE_FLAG);
}

int main(int argc, char** argv) {
    if (argc != 4) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    const bool decode = strcmp(argv[1], DECODE_FLAG) == 0;
    const bool encode = strcmp(argv[1], ENCODE_FLAG) == 0;
    const char* inpath = argv[2];
    const char* outpath = argv[3];

    if (decode == encode) {
        LOG_MSG(error, "%s and %s are mutually exclusive and mandatory\n");
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    if (decode) {
        aria_decode(inpath, outpath);
    } else {
        aria_encode(inpath, outpath);
    }

    return EXIT_SUCCESS;
}
