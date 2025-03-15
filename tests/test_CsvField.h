#include "../csvee.h"
#include <assert.h>

// void csvee_print_field(const CsvField *field);

void test_field_intailization()
{
    CsvField field = csvee_create_field("hello");
    assert(field.value != NULL);
    assert(strcmp(field.value, "hello") == 0);

    csvee_free_field(&field);
    // assert(field.value == NULL); //
};

void test_field_convention()
{
    CsvField fname = csvee_create_field("Sackey Ezekiel");
    CsvField fage = csvee_create_field("20");
    CsvField fweight = csvee_create_field("63.5");
    CsvField fis_student = csvee_create_field("1");

    char *name = csv_field_to_string(&fname);
    assert(name != NULL);
    assert(strcmp(name, "Sackey Ezekiel") == 0);

    int age = csv_field_to_integer(&fage);
    assert(age == 20);

    double weight = csv_field_to_double(&fweight);
    assert(weight == 63.5);

    int is_student = csv_field_to_boolean(&fis_student);
    assert(is_student == 1);
};

void test_field_operators()
{
    CsvField name = csvee_create_field("Sackey");
    CsvField name2 = csvee_create_field("Ezekiel");
    assert(!csvee_field_equal(&name, &name2));

    CsvField name3 = csvee_create_field("Sackey");
    assert(csvee_field_equal(&name, &name3));

    CsvField age = csvee_create_field("20");
    CsvField age2 = csvee_create_field("1");
    assert(!csvee_field_equal(&age, &age2));

    CsvField age3 = csvee_create_field("20");
    assert(csvee_field_equal(&age, &age3));
};

void test_field()
{
    test_field_intailization();
    test_field_convention();
    test_field_operators();

    printf("All Field Test Passed\n");
};
