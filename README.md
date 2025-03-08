# CSV Parser in C 📄

MyCSV is a simple C library for parsing, creating, and printing CSV files.
It provides functions to create and manage CSV fields, rows, and files, as well as to parse CSV files from disk and print them to the console.
The parser reads a CSV file and stores the data in a structured format, allowing easy access and manipulation of the CSV data.

## Csvee Data Structures 🗂️

### `Csvee`

A structure to hold the parsed CSV data.

```c
typedef struct Csvee {
    CsvRow *rows;
    size_t count;
} Csvee;
```

- `rows`: A 2D array of strings representing the CSV data.
- `count`: The number of rows in the CSV data.

## Features ✨

- Parses CSV files with support for quoted fields and escaped quotes.
- Dynamically allocates memory to handle CSV files of varying sizes.
- Provides functions to free the allocated memory.
- 📄 Create and manage CSV fields, rows, and files
- 📥 Parse CSV files from disk
- 🖨️ Print CSV files to the console
- 💾 Write CSV files to disk

## Files 📂

- `csvee.h`: Contains the implementation of the CSV parser
- `sample.c` contains `main` function to demonstrate its usage.

## 🛠️ Installation

To use the MyCSV library, simply include the `csvee.h` header file in your project and compile your code with it.

```c
#include "csvee.h"
```

## Usage 🚀

### 📝 Creating a Csvee

You can create a CSV file in memory using the provided functions:

```c
#include "csvee.h"

int main()
{
    // Create a CSV file with 2 rows
    Csvee file = csvee_create_file(2);

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

    // Free the CSV file
    csvee_free_csv(&file);

    return 0;
}
```

### 📥 Reading a CSV File to Csvee.

You can parse a CSV file from disk using the `csv_read_from_csv` function:

```c
#include "csvee.h"

int main()
{
    // Parse the CSV file from "example.csv"
    CsvFile file = csv_read_from_csv("example.csv");

    // Print the parsed CSV file
    csv_print(&file);

    // Free the CSV file
    csv_free_file(&file);

    return 0;
}
```

### 💾 Writing a Cvee to Csv File.

You can write a CSV file to disk using the `csvee_write_to_csv` function:

```c
#include "csvee.h"

int main()
{
    // Create a CSV file with 2 rows
    CsvFile file = csv_create_file(2);

    // Create the first row with 3 fields
    file.rows[0] = csv_create_row(3);
    file.rows[0].fields[0] = csv_create_field("Name");
    file.rows[0].fields[1] = csv_create_field("Age");
    file.rows[0].fields[2] = csv_create_field("Occupation");

    // Create the second row with 3 fields
    file.rows[1] = csv_create_row(3);
    file.rows[1].fields[0] = csv_create_field("John Doe");
    file.rows[1].fields[1] = csv_create_field("30");
    file.rows[1].fields[2] = csv_create_field("Software Engineer");

    // Write the CSV file to "output.csv"
    if (csv_write_to_csv(&file, "output.csv"))
    {
        printf("CSV file written successfully to output.csv\n");
    }
    else
    {
        printf("Failed to write CSV file to output.csv\n");
    }

    // Free the CSV file
    csv_free_file(&file);

    return 0;
}
```

## License 📜

This project is licensed under the MIT License.
