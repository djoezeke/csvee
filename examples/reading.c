#define CSVEE_IMPLEMENTATION
#include "../csvee.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    const char *fname = "../csv/example.csv";
    Csvee_t *csv = csvee_read_from_file(fname);

    if (!csv)
    {
        fprintf(stderr, "failed to read %s\n", fname);
        return 1;
    }

    for (size_t r = 0; r < csv->count; ++r)
    {
        CSVRow_t *row = &csv->rows[r];
        for (size_t c = 0; c < row->count; ++c)
        {
            char *s = csvee_field_to_string(&row->fields[c]);
            if (s)
            {
                printf("[%zu,%zu]=%s\n", r, c, s);
                free(s);
            }
        }
    }

    csvee_free(csv);
    return 0;
}

/**
 * LICENSE: Public Domain (www.unlicense.org)
 *
 * Copyright (c) 2025 Sackey Ezekiel Etrue
 *
 * This is free and unencumbered software released into the public domain.
 * Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
 * software, either in source code form or as a compiled binary, for any purpose,
 * commercial or non-commercial, and by any means.
 * In jurisdictions that recognize copyright laws, the author or authors of this
 * software dedicate any and all copyright interest in the software to the public
 * domain. We make this dedication for the benefit of the public at large and to
 * the detriment of our heirs and successors. We intend this dedication to be an
 * overt act of relinquishment in perpetuity of all present and future rights to
 * this software under copyright law.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */