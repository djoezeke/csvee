#include "csvee.hpp"
#include <stdio.h>

int main(void)
{
    const char *fname = "csv/example.csv";
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
            char *s = csv_field_to_string(&row->fields[c]);
            if (s)
            {
                printf("[%zu,%zu]=%s\n", r, c, s);
                free(s);
            }
        }
    }

    csvee_free_csv(csv);
    return 0;
}
