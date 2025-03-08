#ifndef DJOEZEKE_CSVEE_H
#define DJOEZEKE_CSVEE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// TODO : csvee_get_filed(csvee,row,col);
// TODO : csvee_get_row(csvee,row);
// TODO : csvee_add_row(csvee,fields_count,...values);
// TODO : csvee_update_row(csvee,row);
// TODO : csvee_remove_row(csvee,row);
// TODO : csvee_update_filed(csvee,row,col,value);
// TODO : csvee_delete_field(csvee,row,col);

#pragma region Csvee DEF

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

enum CsvError
{
    UNKNOWN = -1,
    MISSING_SEPARATOR,
    MISSING_VALUE,
};

// Define a structure for a CSV field
typedef struct CsvField
{
    char *value;
} CsvField;

// Define a structure for a CSV row
typedef struct CsvRow
{
    CsvField *fields;
    size_t count;
} CsvRow;

// Define a structure for a CSV file
typedef struct Csvee
{
    CsvRow *rows;
    size_t count;
} Csvee;

CsvField csvee_create_field(const char *value);
void csvee_free_field(CsvField *field);
CsvRow csvee_create_row(size_t field_count);
void csvee_free_row(CsvRow *row);
Csvee csvee_create_csv(size_t row_count);
void csvee_free_csv(Csvee *file);
Csvee csvee_read_from_file(const char *filename);
bool csvee_write_to_file(const Csvee *csvee, const char *filename);
void csvee_print(const Csvee *file);

#pragma endregion // Csvee DEF

#pragma region Csvee IMP

// Function to create a CSV field
CsvField csvee_create_field(const char *value)
{
    CsvField field;
    field.value = strdup(value);
    return field;
}

// Function to free a CSV field
void csvee_free_field(CsvField *field)
{
    free(field->value);
}

// Function to create a CSV row
CsvRow csvee_create_row(size_t field_count)
{
    CsvRow row;
    row.fields = (CsvField *)malloc(field_count * sizeof(CsvField));
    row.count = field_count;
    return row;
}

// Function to free a CSV row
void csvee_free_row(CsvRow *row)
{
    for (size_t i = 0; i < row->count; i++)
    {
        csvee_free_field(&row->fields[i]);
    }
    free(row->fields);
}

// Function to create a CSV file
Csvee csvee_create_csv(size_t row_count)
{
    Csvee file;
    file.rows = (CsvRow *)malloc(row_count * sizeof(CsvRow));
    file.count = row_count;
    return file;
}

// Function to free a CSV file
void csvee_free_csv(Csvee *file)
{
    for (size_t i = 0; i < file->count; i++)
    {
        csvee_free_row(&file->rows[i]);
    }
    free(file->rows);
}

Csvee csvee_read_from_file(const char *filename)
{
    Csvee csvee = {.rows = NULL, .count = 0};

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Could not open file %s\n", filename);
        return csvee;
    }

    char line[MAX_LINE_LENGTH];
    size_t row_capacity = 10;
    size_t col_capacity = 10;

    csvee.rows = (CsvRow *)malloc(row_capacity * sizeof(CsvRow));
    size_t row_num = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (csvee.count >= row_capacity)
        {
            row_capacity *= 2;
            csvee.rows = (CsvRow *)realloc(csvee.rows, row_capacity * sizeof(CsvRow));
        }

        CsvRow row = csvee_create_row(col_capacity);
        char field[MAX_FIELD_LENGTH];
        size_t field_index = 0;
        size_t col_count = 0;
        bool in_quotes = false;

        for (size_t i = 0; i < strlen(line); ++i)
        {
            char ch = line[i];
            if (ch == '"' && (i == 0 || line[i - 1] != '\\'))
            {
                in_quotes = !in_quotes;
            }
            else if (ch == ',' && !in_quotes)
            {
                field[field_index] = '\0';
                row.fields[col_count] = csvee_create_field(field);
                col_count++;
                field_index = 0;

                if (col_count >= col_capacity)
                {
                    col_capacity *= 2;
                    row.fields = (CsvField *)realloc(row.fields, col_capacity * sizeof(CsvField));
                }
            }
            else
            {
                field[field_index++] = ch;
            }
        }
        field[field_index] = '\0';
        row.fields[col_count] = csvee_create_field(field);
        col_count++;

        row.count = col_count;
        csvee.rows[csvee.count] = row;
        csvee.count++;
    }

    fclose(file);
    return csvee;
}

bool csvee_write_to_file(const Csvee *csvee, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        fprintf(stderr, "Could not open file %s for writing\n", filename);
        return false;
    }

    for (size_t i = 0; i < csvee->count; i++)
    {
        for (size_t j = 0; j < csvee->rows[i].count; j++)
        {
            fprintf(file, "%s", csvee->rows[i].fields[j].value);
            if (j < csvee->rows[i].count - 1)
            {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return true;
}

// Function to print a CSV file (for demonstration purposes)
void csvee_print(const Csvee *file)
{
    for (size_t i = 0; i < file->count; i++)
    {
        for (size_t j = 0; j < file->rows[i].count; j++)
        {
            printf("%s", file->rows[i].fields[j].value);
            if (j < file->rows[i].count - 1)
            {
                printf(",");
            }
        }
        printf("\n");
    }
}

#pragma endregion // Csvee IMP

#endif // DJOEZEKE_CSVEE_H