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

    for (CsvIterator_t *ci = csvee_csvee_iter_begin(csv); ci != csvee_csvee_iter_end(csv); csvee_csvee_iter_next(ci))
    {
        CSVRow_t *row = csvee_csvee_iter_peek(ci);
        for (RowIterator_t *ri = csvee_row_iter_begin(row); ri != csvee_row_iter_end(row); csvee_row_iter_next(ri))
        {
            char *s = csvee_field_to_string(csvee_row_iter_peek(ri));
            if (s)
            {
                printf("%s\n", s);
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