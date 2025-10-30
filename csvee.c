/**
 * @file csvee.c
 * @brief Csv/Tsv Reader/Writer Library Source.
 * @details This file provides API usage examples.
 * @author Sackey Ezekiel Etrue (djoezeke)
 * @date Tue 29 10:25:15 Oct GMT 2025
 * @version 0.1.0
 * @see https://www.github.com/djoezeke/csvee
 * @copyright Copyright (c) 2025 Sackey Ezekiel Etrue
 *
 * CSVEE: What this Is
 *
 * DOCUMENTATION:
 *
 * FEATURES:
 *
 * FUTURE:
 *
 * ISSUES:
 *
 * NOTES:
 *
 * USAGE:
 *
 *   Include this file in whatever places need to refer to it.
 *
 *   Do this:
 *      #define CSVEE_IMPLEMENTATION
 *
 *   before you include this file in *one* C or C++ file to create the implementation.
 *
 *   i.e. it should look like this:
 *
 *      #include ...
 *      #include ...
 *      #define CSVEE_IMPLEMENTATION
 *      #include "csvee.h"
 *
 * Example usage:
 * @code
 *
 * # include "csvee.h"
 *
 * using namespace csvee;
 *
 * int main(int argc, char *argv[]) {
 *
 * 	  ...
 *
 *	  CSVReader reader("sample.csv");
 *
 *	  for (CSVRow& row: reader) {
 *		  for (CSVField& field: row) {
 *			  // By default, get<>() produces a std::string.
 *			  std::cout << field.get<>() << ...
 *	  	  }
 * 	  }
 *
 *	  ...
 *
 *    return 0;
 * }
 *
 * @endcode
 *
 * @code
 *
 * # include "csvee.h"
 *
 * using namespace csvee;
 *
 * int main(int argc, char *argv[]) {
 *
 * 	  ...
 *
 *	  CSVWriter  writer("sample.csv");
 *
 *	  writer << vector<string>({ "Name", "Age", "Occupation" }) ;
 *	  writer << vector<string>({ "John Doe", "30", "Software Engineer" }) ;
 *	  writer << vector<string>({ "Zeke Cora", "20", "Computer Scientist" }) ;
 *
 *	  ...
 *
 *    return 0;
 * }
 *
 * @endcode
 *
 * FAQS:
 *
 * TODO:
 *
 * Index of this file:
 *
 *  [SECTION] Reading C API
 *  [SECTION] Writing C API
 *  [SECTION] Read/Write C API
 *  [SECTION] Reading C++ API
 *  [SECTION] Writing C++ API
 *  [SECTION] Read/Write C++ API
 *
 *
 * RESOURCES:
 * - Homepage ................... https://github.com/djoezeke/csvee
 * - Releases & changelog ....... https://github.com/djoezeke/csvee/releases
 * - Issues & support ........... https://github.com/djoezeke/csvee/issues
 *
 * LICENSE:
 *      See end of file for license information.
 *
 */

#define CSVEE_IMPLEMENTATION
#include "csvee.h"

//-----------------------------------------------------------------------------
// [SECTION] C Examples
//-----------------------------------------------------------------------------

/**
 * Reading CSV
 */
#if 0

int main(int argc, char const *argv[])
{

    Csvee_t *csvee = csvee_read_from_file("csvfile.csv");

    CSVRow_t *row;

    while (row = csvee_read_next_row(csvee))
    {
        CSVField_t *field;

        while (field = csvee_read_next_col(csvee, row))
        {
            csvee_field_to_string(field);
        }
    }

    return 0;
}

#endif

/**
 * Writing CSV
 */
#if 0


int main(int argc, char const *argv[])
{

    return 0;
}

#endif

/**
 * Reading/Writing CSV
 */
#if 0

int main(int argc, char const *argv[])
{

    return 0;
}

#endif

//-----------------------------------------------------------------------------
// [SECTION] C++ Examples
//-----------------------------------------------------------------------------

#ifdef __cplusplus

/**
 * Reading CSV
 */
#if 0

using namespace csvee;

int main(int argc, char const *argv[])
{

    CSVReader reader("csv/sample.csv");
    
    for (CSVRow& row: reader) {
        for (CSVField& field: row) {
            // By default, get<>() produces a std::string.
            std::cout << field.get<>() << std::end;
        }
    }

    return 0;
}

#endif

/**
 * Writing CSV
 */
#if 0

using namespace csvee;

int main(int argc, char const *argv[])
{

	CSVWriter  writer("sample.csv");

	writer << vector<string>({ "Name", "Age", "Occupation" }) ;
	writer << vector<string>({ "John Doe", "30", "Software Engineer" }) ;
	writer << vector<string>({ "Zeke Cora", "20", "Computer Scientist" }) ;

    return 0;
}

#endif

/**
 * Reading/Writing CSV
 */
#if 0

int main(int argc, char const *argv[])
{

    return 0;
}

#endif

#endif // __cplusplus

/**
 * LICENSE: MIT License
 *
 * Copyright (c) 2025 Sackey Ezekiel Etrue
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */