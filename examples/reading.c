#define CSVEE_SEPERATOR ','

#include "../csvee.h"

int main()
{
    // Create a CSV file with 5 rows
    Csvee_t file = csvee_create_csv();

    // // Create the first row with 3 fields
    // file.rows[0] = csvee_create_row(3);
    // file.rows[0].fields[0] = csvee_create_field("Name");
    // file.rows[0].fields[1] = csvee_create_field("Age");
    // file.rows[0].fields[2] = csvee_create_field("Occupation");

    // // Create the second row with 3 fields
    // file.rows[1] = csvee_create_row(3);
    // file.rows[1].fields[0] = csvee_create_field("John Doe");
    // file.rows[1].fields[1] = csvee_create_field("30");
    // file.rows[1].fields[2] = csvee_create_field("Software Engineer");

    // csvee_add_row(&file, 3, "Rita Sackey", "30", "Rich \"Mom\"");
    // csvee_add_row(&file, 3, "Sackey", "30", "Rich Mom");
    // csvee_add_row(&file, 3, "Rita Sackey", "30", "Rich \"Mom\"");
    // csvee_add_row(&file, 3, "Sackey", "30", "Rich Mom");
    // csvee_add_row(&file, 3, "Rita Sackey", "30", "Rich \"Mom\"");
    // csvee_add_row(&file, 3, "Sackey", "30", "Rich Mom");
    // csvee_add_row(&file, 3, "Rita Sackey", "30", "Rich \"Mom\"");
    // csvee_add_row(&file, 3, "Sackey", "30", "Rich Mom");
    // csvee_add_row(&file, 3, "Rita Sackey", "30", "Rich \"Mom\"");
    // csvee_add_row(&file, 3, "Sackey", "30", "Rich Mom");

    // // Print the CSV file
    // csvee_print_csv(&file);

    // const char *name = csvee_get_filed(&file, 1, 1);
    // printf("%s\n", name);

    // CsvRow row = csvee_get_row(&file, 1);
    // csvee_print_row(&row);

    Csvee_t file2 = csvee_read_from_file("csv/example.csv");
    csvee_print_csv(&file2);

    // Free the CSV file
    csvee_free_csv(&file);
    // csvee_free_csv(&file2);

    return 0;
}