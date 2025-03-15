#include "../csvee.h"
#include <assert.h>

// Csvee csvee_create_csv();
// Csvee csvee_copy_csv(const Csvee *file);
// void csvee_print_csv(const Csvee *file);
// void csvee_free_csv(Csvee *file);

void test_file_intailization()
{
    // Create a CSV file with 5 rows
    Csvee file = csvee_create_csv();
    assert(file.rows != NULL);
    assert(file.count == 0);
    assert(file.size == 5);

    csvee_free_csv(&file);
    // assert(file.rows == NULL); //
    assert(file.count == 0);
    assert(file.size == 0);
};

void test_file_row_operations()
{
    Csvee file = csvee_create_csv();

    // Create the first row with 3 fields
    file.rows[0] = csvee_create_row(3);
    file.rows[0].fields[0] = csvee_create_field("Name");
    file.rows[0].fields[1] = csvee_create_field("Age");
    file.rows[0].fields[2] = csvee_create_field("Occupation");
    file.count++;

    assert(file.rows[0].fields[0].value != NULL);
    assert(strcmp(file.rows[0].fields[0].value, "Name") == 0);

    assert(file.rows[0].fields[1].value != NULL);
    assert(strcmp(file.rows[0].fields[1].value, "Age") == 0);

    assert(file.rows[0].fields[2].value != NULL);
    assert(strcmp(file.rows[0].fields[2].value, "Occupation") == 0);

    csvee_add_row(&file, 3, "Sackey", "20", "Software Engineer");
    // assert(csvee_row_exist(&file, 2));

    assert(file.rows[1].fields[0].value != NULL);
    assert(strcmp(file.rows[1].fields[0].value, "Sackey") == 0);

    assert(file.rows[1].fields[1].value != NULL);
    assert(strcmp(file.rows[1].fields[1].value, "20") == 0);

    assert(file.rows[1].fields[2].value != NULL);
    assert(strcmp(file.rows[1].fields[2].value, "Software Engineer") == 0);

    csvee_update_row(&file, 2, 3, "Ezekiel", "19", "Computer Scientist");

    assert(strcmp(file.rows[1].fields[0].value, "Ezekiel") == 0);
    assert(strcmp(file.rows[1].fields[1].value, "19") == 0);
    assert(strcmp(file.rows[1].fields[2].value, "Computer Scientist") == 0);

    // csvee_delete_row(&file, 2);//
    // assert(file.rows[1].fields[0].value == NULL);
    // assert(file.rows[1].fields[1].value == NULL);
    // assert(file.rows[1].fields[2].value == NULL);

    assert(csvee_row_exist(&file, 1));
    // assert(!csvee_row_exist(&file, 2));

    // CsvRow csvee_get_row(Csvee *csvee, size_t row);
    // void csvee_print_row(const CsvRow *row);

    csvee_free_csv(&file);
};

void test_file_field_operations()
{
    Csvee file = csvee_create_csv();

    // Create the first row with 3 fields
    file.rows[0] = csvee_create_row(3);
    file.rows[0].fields[0] = csvee_create_field("Name");
    file.rows[0].fields[1] = csvee_create_field("Age");
    file.rows[0].fields[2] = csvee_create_field("Occupation");
    file.count++;

    assert(file.rows[0].fields[0].value != NULL);
    assert(strcmp(file.rows[0].fields[0].value, "Name") == 0);

    assert(file.rows[0].fields[1].value != NULL);
    assert(strcmp(file.rows[0].fields[1].value, "Age") == 0);

    assert(file.rows[0].fields[2].value != NULL);
    assert(strcmp(file.rows[0].fields[2].value, "Occupation") == 0);

    csvee_update_field(&file, 1, 3, "Major");
    assert(strcmp(file.rows[0].fields[2].value, "Major") == 0);

    assert(csvee_field_exist(&file, 1, 1));
    assert(!csvee_field_exist(&file, 1, 5));

    csvee_delete_field(&file, 1, 3);
    assert(!csvee_field_exist(&file, 1, 3));

    csvee_free_csv(&file);
};

void test_file()
{
    test_file_intailization();
    test_file_row_operations();
    test_file_field_operations();
    printf("All File Test Passed\n");
};
