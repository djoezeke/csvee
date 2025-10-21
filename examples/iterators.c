#define CSVEE_IMPLEMENTATION
#include "../csvee.h"
#include <stdio.h>

int main(void)
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
