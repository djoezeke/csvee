#include "../csvee.h"
#include <assert.h>


void test_row_intailization()
{
    CsvRow row1 = csvee_create_row(3);
    row1.fields[0] = csvee_create_field("Name");
    row1.fields[1] = csvee_create_field("Age");
    row1.fields[2] = csvee_create_field("Occupation");

    assert(row1.fields[0].value != NULL);
    assert(row1.fields[1].value != NULL);
    assert(row1.fields[2].value != NULL);

    assert(strcmp(row1.fields[0].value, "Name") == 0);
    assert(strcmp(row1.fields[1].value, "Age") == 0);
    assert(strcmp(row1.fields[2].value, "Occupation") == 0);

    csvee_free_row(&row1);

    // assert(row1.fields == NULL);//
    assert(row1.count == 0);
};

void test_row_operators()
{
    CsvRow row1 = csvee_create_row(3);
    row1.fields[0] = csvee_create_field("Name");
    row1.fields[1] = csvee_create_field("Age");
    row1.fields[2] = csvee_create_field("Occupation");

    CsvRow row2 = csvee_create_row(3);
    row2.fields[0] = csvee_create_field("Ezekiel");
    row2.fields[1] = csvee_create_field("20");
    row2.fields[2] = csvee_create_field("Software Engineer");

    assert(row1.count == row2.count);
    assert(!csvee_row_equal(&row1, &row2));
};

void test_row()
{
    test_row_intailization();
    test_row_operators();

    printf("All Row Test Passed\n");
};
