#include <stdlib.h>
#include <stdio.h>

#include <common/file.h>

bool aria_transcode(const char* inpath, const char* outpath, bool is_encode) {
    FILE* f = fopen(outpath, "wb");
    if (f == NULL) {
        return false;
    }

    u8* data = file_load(inpath);
    const u32 size = file_size(inpath);

    if (is_encode) {
        for (u32 i = 0; i < size; i++) {
            const u8 byte = data[i];
            for (u8 bit = 0; bit < 8; bit++) {
                const bool val = (byte >> bit) & 1;
                fprintf(f, "%c", val ? '7' : ' ');
            }
        }
    } else {
        for (u32 i = 0; i < size / 8; i++) {
            u8 byte = 0;
            for (u8 bit = 0; bit < 8; bit++) {
                const char c = data[(i * 8) + bit];
                const u8 val = c == '7';

                byte >>= 1;
                byte |= (val << 7);
            }
            fwrite(&byte, sizeof(byte), 1, f);
        }
    }

    free(data);
    fclose(f);
    return true;
}
