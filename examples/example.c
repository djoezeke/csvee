#include "../csvee.h"

int main()
{
    // Create a CSV file with 2 rows
    Csvee file = csvee_create_csv(2);

    // Create the first row with 3 fields
    file.rows[0] = csvee_create_row(3);
    file.rows[0].fields[0] = csvee_create_field("Name");
    file.rows[0].fields[1] = csvee_create_field("Age");
    file.rows[0].fields[2] = csvee_create_field("Occupation");

    // Create the second row with 3 fields
    file.rows[1] = csvee_create_row(3);
    file.rows[1].fields[0] = csvee_create_field("John Doe");
    file.rows[1].fields[1] = csvee_create_field("30");
    file.rows[1].fields[2] = csvee_create_field("Software Engineer");

    // Print the CSV file
    csvee_print(&file);

    Csvee file2 = csvee_read_from_file("example.csv");

    csvee_print(&file2);

    // Free the CSV file
    csvee_free_csv(&file);

    return 0;
}