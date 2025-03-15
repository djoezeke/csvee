#define CSVEE_SEPERATOR ','

#include "../csvee.h"
#include "test_CsvField.h"
#include "test_CsvRow.h"
#include "test_CsvFile.h"

int main()
{
    test_field();
    test_row();
    test_file();
    return 0;
}