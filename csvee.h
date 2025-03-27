#ifndef DJOEZEKE_CSVEE_H
#define DJOEZEKE_CSVEE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

#ifdef __cplusplus

#include <fstream>
#include <iostream>
#include <vector>
#include <exception>

#endif //__cplusplus

#define CSVEE_VERSION_MAJOR 0
#define CSVEE_VERSION_MINOR 1
#define CSVEE_VERSION_PATCH 0

#define CSVEE_DEBUG

#ifdef CSVEE_DEBUG
#endif // CSVEE_DEBUG

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

/**
 * @brief Macro to convert an error value to its string representation.
 *
 * This macro is used in a switch-case statement to return the string representation
 * of an error value.
 *
 * @param value The error value to convert to a string.
 */
#define CASEFY_ERROR(value) \
    case value:             \
        return #value;

#pragma region STRUCTURES

typedef enum CsveeError_t
{
    UNKNOWN = -1,

    NO_SEPARATOR,
    MISSING_VALUE,

    INVALID_FIELD, // if filed doesnt exits
    EMPTY_FIELD,
    NULL_FIELD,

    INVALID_ROW,
    NULL_ROW,

    INVALID_FILE, // if
    NULL_FILE,    // if pointer is null
    FILE_ERROR,

    VALUE_NULL,
    WRONG_CAST
} CsveeError_t;

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
typedef struct Csvee_t
{
    CsvRow *rows;
    size_t count;
    size_t size;
    char sep;
} Csvee_t;

#ifdef __cplusplus

/**
 * @brief CsveeError class for Csvee-related errors.
 */
class CsveeError : public std::exception
{
public:
    /**
     * @brief Default constructor.
     */
    CsveeError();

    /**
     * @brief Constructs an exception with a specific error type.
     * @param type The type of the error.
     */
    CsveeError(CsveeError_t type);

    /**
     * @brief Constructs an exception with a specific message and error type.
     * @param message The error message.
     * @param type The type of the error.
     */
    CsveeError(const std::string &message, CsveeError_t type);

    /**
     * @brief Gets the error message.
     * @return The error message.
     */
    const char *what() const noexcept override;

    /**
     * @brief Gets the error type.
     * @return The error type.
     */
    CsveeError_t GetErrType() const noexcept;

    /**
     * @brief Gets the name of the error type.
     * @param error The error type.
     * @return The name of the error type.
     */
    std::string GetErrName(CsveeError_t error) const noexcept;

private:
    mutable std::string m_Msg; //!< The error message.
    CsveeError_t m_ErrType;    //!< The error type.
};

class Csvee
{
private:
    Csvee_t m_Csvee_t;

protected:
    char m_Seperator;

public:
    Csvee(char seperator);
    Csvee();

    CsvRow GetRow(int row);
    CsvField GetField(int col);
    Csvee_t GetFile();

    void AddRow(int row);
    int RowExits(int row);
    void ReadFile(std::fstream file) {};
    void WriteFile(std::string file_path) {};

    std::string Stringify();

    ~Csvee();
};

#endif // __cplusplus

#pragma endregion // STRUCTURES

#pragma region DECLARATIONS

double csv_field_to_double(CsvField *field);
int csv_field_to_integer(CsvField *field);
char *csv_field_to_string(CsvField *field);
int csv_field_to_boolean(CsvField *field);

CsvField csvee_create_field(const char *value);
CsvField csvee_get_filed(Csvee_t *csvee, size_t row, size_t col);

CsvRow csvee_create_row(size_t field_count);
CsvRow csvee_get_row(Csvee_t *csvee, size_t row);

Csvee_t csvee_create_csv(char sep);
Csvee_t csvee_copy_csv(const Csvee_t *file);

int csvee_update_field(Csvee_t *csvee, size_t row, size_t col, const char *value);
int csvee_delete_field(Csvee_t *csvee, size_t row, size_t col);
int csvee_field_exist(Csvee_t *csvee, size_t row, size_t col);
int csvee_field_equal(CsvField *field, CsvField *other);

int csvee_add_row(Csvee_t *csvee, size_t fields_count, ...);
int csvee_update_row(Csvee_t *csvee, size_t row, size_t fields_count, ...);
int csvee_delete_row(Csvee_t *csvee, size_t row);
int csvee_row_exist(Csvee_t *csvee, size_t row);
int csvee_row_equal(CsvRow *row, CsvRow *other);

Csvee_t csvee_read_from_file(const char *filename);
bool csvee_write_to_file(const Csvee_t *csvee, const char *filename);

void csvee_error(CsveeError_t error, const char *format, ...);
const char *csvee_error_name(CsveeError_t error);

void csvee_field_str(const CsvField *field, char **buffer, size_t *size);
void csvee_row_str(const CsvRow *row, char sep, char **buffer, size_t *size);
void csvee_csv_str(const Csvee_t *csvee, char **buffer, size_t *size);

void csvee_free_field(CsvField *field);
void csvee_free_row(CsvRow *row);
void csvee_free_csv(Csvee_t *csvee);

#pragma endregion // DECLARATIONS

#pragma region DEFINATIONS

double csv_field_to_double(CsvField *field)
{
    if (field == NULL)
    {
#ifdef CSVEE_DEBUG
        csvee_error(NULL_FIELD, "Field is NULL\n");
#endif // CSVEE_DEBUG
        return -1.0;
    }

    return atof(field->value);
};

int csv_field_to_integer(CsvField *field)
{
    if (field == NULL)
    {
#ifdef CSVEE_DEBUG
        csvee_error(NULL_FIELD, "Field is NULL\n");
#endif // CSVEE_DEBUG
        return -1;
    }

    return atoi(field->value);
};

char *csv_field_to_string(CsvField *field)
{
    if (field == NULL)
    {
#ifdef CSVEE_DEBUG
        csvee_error(NULL_FIELD, "Field is NULL\n");
#endif // CSVEE_DEBUG
        return NULL;
    }

    return field->value;
};

int csv_field_to_boolean(CsvField *field)
{
    int ret;

    if (field == NULL)
    {
#ifdef CSVEE_DEBUG
        csvee_error(NULL_FIELD, "Field is NULL\n");
#endif // CSVEE_DEBUG
        return -1;
    }
    if (strcmp(field->value, "0") == 0)
    {
        ret = 0;
    }

    if (strcmp(field->value, "1") == 0)
    {
        ret = 1;
    }

    return ret;
};
// Function to create a CSV field
CsvField csvee_create_field(const char *value)
{
    CsvField field;
    field.value = strdup(value);
    return field;
}

CsvField csvee_get_filed(Csvee_t *csvee, size_t row, size_t col)
{
    CsvField field = csvee_create_field("");

    if (csvee->count < row)
    {
#ifdef CSVEE_DEBUG
        csvee_error(INVALID_ROW, "Row (%d) : is out of range\n", row);
#endif // CSVEE_DEBUG
        return field;
    }

    if (csvee->rows[row - 1].count < col)
    {
#ifdef CSVEE_DEBUG
        csvee_error(INVALID_FIELD, "Field (%d) : is out of range\n", col);
#endif // CSVEE_DEBUG
        return field;
    }

    field.value = strdup(csvee->rows[row - 1].fields[col - 1].value);
    return field;
};

// Function to create a CSV row
CsvRow csvee_create_row(size_t field_count)
{
    CsvRow row;
    row.fields = (CsvField *)malloc(field_count * sizeof(CsvField));
    row.count = field_count;
    return row;
}

CsvRow csvee_get_row(Csvee_t *csvee, size_t row)
{
    CsvRow nrow = csvee_create_row(0);

    if (csvee->count < row)
    {
#ifdef CSVEE_DEBUG
        csvee_error(INVALID_ROW, "Row (%d) : is out of range\n", row);
#endif // CSVEE_DEBUG
        return nrow;
    }

    nrow = csvee->rows[row - 1];
    return nrow;
};

// Function to create a CSV file
Csvee_t csvee_create_csv(char sep)
{
    Csvee_t file;
    file.count = 0;
    file.size = 5;
    file.rows = (CsvRow *)malloc(file.size * sizeof(CsvRow));
    file.sep = sep;
    return file;
}

Csvee_t csvee_copy_csv(const Csvee_t *file)
{
    Csvee_t copy = *file;
    copy.count = file->count;
    copy.rows = file->rows;
    copy.size = file->size;
    return copy;
};

int csvee_update_field(Csvee_t *csvee, size_t row, size_t col, const char *value)
{
    if (csvee->count < row)
    {
#ifdef CSVEE_DEBUG
        csvee_error(INVALID_ROW, "Row (%d) : is out of range\n", row);
#endif // CSVEE_DEBUG
        return 0;
    }

    if (csvee->rows[row - 1].count < col)
    {
#ifdef CSVEE_DEBUG
        csvee_error(INVALID_FIELD, "Field (%d) : is out of range\n", col);
#endif // CSVEE_DEBUG
        return 0;
    }

    csvee->rows[row - 1].fields[col - 1].value = strdup(value);
    return 1;
};

int csvee_delete_field(Csvee_t *csvee, size_t row, size_t col)
{
    if (csvee == NULL)
    {
#ifdef CSVEE_DEBUG
        csvee_error(NULL_FILE, "File is null\n");
#endif // CSVEE_DEBUG
        return 0;
    }

    if (csvee->count < row)
    {
#ifdef CSVEE_DEBUG
        csvee_error(INVALID_ROW, "Row (%d) : is out of range\n", row);
#endif // CSVEE_DEBUG
        return 0;
    }

    if (csvee->rows[row - 1].count < col)
    {
#ifdef CSVEE_DEBUG
        csvee_error(INVALID_FIELD, "Field (%d) : is out of range\n", col);
#endif // CSVEE_DEBUG
        return 0;
    }

    csvee->rows[row - 1].fields[col - 1].value = "";
    csvee->rows[row - 1].count--;

    return 1;
};

int csvee_field_exist(Csvee_t *csvee, size_t row, size_t col)
{
    if (csvee == NULL)
    {
#ifdef CSVEE_DEBUG
        csvee_error(NULL_FILE, "File is null\n");
#endif // CSVEE_DEBUG
        return 0;
    }

    if (csvee->count < row)
    {
#ifdef CSVEE_DEBUG
        csvee_error(INVALID_ROW, "Row (%d) : is out of range\n", row);
#endif // CSVEE_DEBUG
        return 0;
    }

    if (csvee->rows[row - 1].count < col)
    {
#ifdef CSVEE_DEBUG
        csvee_error(INVALID_FIELD, "Field (%d) : is out of range\n", col);
#endif // CSVEE_DEBUG
        return 0;
    }
    return 1;
};

int csvee_field_equal(CsvField *field, CsvField *other)
{
    return strcmp(field->value, other->value) == 0;
};

int csvee_add_row(Csvee_t *csvee, size_t fields_count, ...)
{
    va_list args;

    // Initialize the argument list
    va_start(args, fields_count);

    if (csvee->count >= csvee->size)
    {
        csvee->size *= 2;
        csvee->rows = (CsvRow *)realloc(csvee->rows, csvee->size * sizeof(CsvRow));
    }

    csvee->rows[csvee->count] = csvee_create_row(fields_count);

    // Loop through all the arguments
    for (size_t i = 0; i < fields_count; i++)
    {
        csvee->rows[csvee->count].fields[i] = csvee_create_field(va_arg(args, const char *));
    }

    csvee->count++;

    // Clean up the argument list
    va_end(args);
};

// Helper function to append formatted text to a string buffer
void append_to_buffer(char **buffer, size_t *size, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    size_t needed = vsnprintf(NULL, 0, format, args) + 1;
    va_end(args);

    *buffer = (char *)realloc(*buffer, *size + needed);
    va_start(args, format);
    vsnprintf(*buffer + *size, needed, format, args);
    va_end(args);

    *size += needed - 1;
}

int csvee_update_row(Csvee_t *csvee, size_t row, size_t fields_count, ...)
{
    va_list args;
    va_start(args, fields_count);

    for (size_t i = 0; i < fields_count; i++)
    {
        csvee->rows[row - 1].fields[i].value = strdup(va_arg(args, char *));
    }

    va_end(args);
    return 1;
};

int csvee_delete_row(Csvee_t *csvee, size_t row)
{
    csvee_free_row(&csvee->rows[row - 1]);
    return 1;
};

int csvee_row_exist(Csvee_t *csvee, size_t row)
{
    if (csvee->count < row)
    {
#ifdef CSVEE_DEBUG
        csvee_error(INVALID_ROW, "Row (%d) : is out of range\n", row);
#endif // CSVEE_DEBUG
        return 0;
    }
    return 1;
};

int csvee_row_equal(CsvRow *row, CsvRow *other)
{
    if (row->count != other->count)
    {
        return 0;
    }

    for (size_t i = 0; i < row->count; i++)
    {
        if (!csvee_field_equal(&row->fields[i], &other->fields[i]))
        {
            return 0;
        }
    }

    return 1;
};

Csvee_t csvee_read_from_file(const char *filename)
{
    Csvee_t csvee = csvee_create_csv();

    FILE *file = fopen(filename, "r");
    if (!file)
    {

#ifdef CSVEE_DEBUG
        csvee_error(NULL_FILE, "Could not open file %s\n", filename);
#endif // CSVEE_DEBUG

        return csvee;
    }

    char line[MAX_LINE_LENGTH];
    // size_t row_capacity = 10;
    size_t col_capacity = 10;

    // csvee.rows = (CsvRow *)malloc(csvee.size * sizeof(CsvRow));

    while (fgets(line, sizeof(line), file))
    {
        if (csvee.count >= csvee.size)
        {
            csvee.size *= 2;
            csvee.rows = (CsvRow *)realloc(csvee.rows, csvee.size * sizeof(CsvRow));
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
            else if (ch == CSVEE_SEPERATOR && !in_quotes)
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
            else if (ch == '\n')
            {
                ++i; // to skip the newline charater
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

bool csvee_write_to_file(const Csvee_t *csvee, const char *filename)
{
    FILE *file = fopen(filename, "w");

    if (!file)
    {
#ifdef CSVEE_DEBUG
        csvee_error(NULL_FILE, "Could not open file %s for writing\n", filename);
#endif // CSVEE_DEBUG
        return false;
    }

    char *buffer;
    size_t size;
    csvee_csv_str(csvee, &buffer, &size);

    fwrite(&buffer, size, 1, file);
    fclose(file);
    return true;
}

void csvee_error(CsveeError_t error, const char *format, ...)
{
    if (format == NULL)
        fprintf(stderr, "CSVEE [%i] : %s \n", error, csvee_error_name(error));
    else
    {
        va_list args;

        va_start(args, format);

        fprintf(stderr, "CSVEE [%i] :", error);
        vprintf(format, args);

        // Clean up the argument list
        va_end(args);
    }
};

const char *csvee_error_name(CsveeError_t error)
{
    switch (error)
    {
        CASEFY_ERROR(UNKNOWN);

        CASEFY_ERROR(NO_SEPARATOR);
        CASEFY_ERROR(MISSING_VALUE);

        CASEFY_ERROR(EMPTY_FIELD);

        CASEFY_ERROR(INVALID_FIELD);
        CASEFY_ERROR(INVALID_ROW);

        CASEFY_ERROR(INVALID_FILE);
        CASEFY_ERROR(NULL_FILE);

        CASEFY_ERROR(NULL_FIELD);
        CASEFY_ERROR(NULL_ROW);

        CASEFY_ERROR(FILE_ERROR);

        CASEFY_ERROR(VALUE_NULL);

        CASEFY_ERROR(WRONG_CAST);
    }
    return "";
};

void csvee_field_str(const CsvField *field, char **buffer, size_t *size)
{
    if (field == NULL)
    {
#ifdef CSVEE_DEBUG
        csvee_error(NULL_FIELD, "Field is null.\n");
#endif // CSVEE_DEBUG
        return;
    }

    append_to_buffer(buffer, size, field->value);
};

void csvee_row_str(const CsvRow *row, char sep, char **buffer, size_t *size)
{
    for (size_t i = 0; i < row->count; i++)
    {
        csvee_field_str(&row->fields[i], buffer, size);
        if (i < row->count - 1)
        {
            append_to_buffer(buffer, size, "%c", sep);
        }
    }
    append_to_buffer(buffer, size, "\n");
};

void csvee_csv_str(const Csvee_t *file, char **buffer, size_t *size)
{
    for (size_t i = 0; i < file->count; i++)
    {
        csvee_row_str(&file->rows[i], &file->sep, buffer, size);
    }
}

void csvee_free_field(CsvField *field)
{
    free(field->value);
}

void csvee_free_row(CsvRow *row)
{
    for (size_t i = 0; i < row->count; i++)
    {
        csvee_free_field(&row->fields[i]);
    }

    row->count = 0;
    free(row->fields);
}

void csvee_free_csv(Csvee_t *file)
{
    for (size_t i = 0; i < file->count; i++)
    {
        csvee_free_row(&file->rows[i]);
    }
    file->count = 0;
    file->size = 0;
    free(file->rows);
}
#ifdef __cplusplus

CsveeError::CsveeError()
{
    m_ErrType = UNKNOWN;
    m_Msg = std::string("(") + GetErrName(UNKNOWN) + std::string(") -> ") + std::string("UNKNOWN ERROR TYPE");
};

CsveeError::CsveeError(CsveeError_t errorType)
{
    m_ErrType = errorType;
    m_Msg = std::string("(") + GetErrName(errorType) + std::string(") -> ") + std::string("ERROR MESSAGE EMPTY");
};

CsveeError::CsveeError(const std::string &message, CsveeError_t errorType)
{
    m_ErrType = errorType;
    m_Msg = std::string("(") + GetErrName(errorType) + std::string(") -> ") + message;
};

const char *CsveeError::what() const noexcept
{
    return m_Msg.c_str();
};

CsveeError_t CsveeError::GetErrType() const noexcept
{
    return m_ErrType;
};

std::string CsveeError::GetErrName(CsveeError_t error) const noexcept
{
    std::string name = csvee_error_name(error);
    return name;
};

#endif //__cplusplus

#pragma endregion // DEFINATIONS

#endif // DJOEZEKE_CSVEE_H