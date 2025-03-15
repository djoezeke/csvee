#define CSVEE_SEPERATOR ','

#include "../csvee.h"

int main()
{
    Csvee file = csvee_read_from_file("csv/example.csv");
    csvee_print_csv(&file);
    CsvField field = csvee_get_filed(&file, 2, 2);
    int age = tsv_field_to_integer(&field);

    // Free the CSV file

    csvee_print_field(&field);
    printf("%d", age);
    // csvee_free_csv(&file2);

    csvee_free_csv(&file);

    return 0;
}