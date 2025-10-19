/* -*- C++ -*- compatibility header. */

#ifndef DJOEZEKE_CSVEE_H
#define DJOEZEKE_CSVEE_H

/**
 * @defgroup version Version Information
 * @brief Macros for library versioning.
 * @{
 */

/**
 * @def CSVEE_VERSION_MAJOR
 * @brief Major version number of the library.
 */
#define CSVEE_VERSION_MAJOR 0

/**
 * @def CSVEE_VERSION_MINOR
 * @brief Minor version number of the library.
 */
#define CSVEE_VERSION_MINOR 1

/**
 * @def CSVEE_VERSION_PATCH
 * @brief Patch version number of the library.
 */
#define CSVEE_VERSION_PATCH 0

/**
 * @def CSVEE_VERSION
 * @brief Library version string in the format @c "X.Y.Z",
 * where @c X is the major version number, @c Y is a minor version
 * number, and @c Z is the patch version number.
 */
#define CSVEE_VERSION "0.1.0"

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Header mess
//-----------------------------------------------------------------------------

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus

#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#endif //__cplusplus

#ifdef CSVEE_DEBUG
#endif // CSVEE_DEBUG

//-----------------------------------------------------------------------------
// [SECTION] Configurable Macros
//-----------------------------------------------------------------------------

/* Default separator if not provided */
#ifndef CSVEE_SEPERATOR
#define CSVEE_SEPERATOR ','
#endif

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

/**
 * @brief Macro to convert an error value to its string representation.
 *
 * This macro is used in a switch-case statement to return the string
 * representation of an error value.
 *
 * @param value The error value to convert to a string.
 */
#define CASEFY_ERROR(value) \
	case value:             \
		return #value;

//-----------------------------------------------------------------------------
// [SECTION] Platform
//-----------------------------------------------------------------------------

/**
 * @defgroup platform Platform Definitions
 * @{
 */

/**
 * @brief   Checks if the compiler is of given brand.
 * @param   name Platform, like `APPLE`.
 * @retval  true   It is.
 * @retval  false  It isn't.
 */
#define CSVEE_PLATFORM_IS(name) CSVEE_PLATFORM_IS_##name

/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */

#ifdef __APPLE__
/**
 * A preprocessor macro that is only defined if compiling for MacOS.
 */
#define CSVEE_PLATFORM_IS_APPLE 1
/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */
#define CSVEE_PLATFORM_NAME_IS "Apple"
#elif defined(linux) || defined(__linux) || defined(__linux__)
/**
 * A preprocessor macro that is only defined if compiling for Linux.
 */
#define CSVEE_PLATFORM_IS_LINUX 1
/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */
#define CSVEE_PLATFORM_NAME_IS "Linux"
#elif defined(WIN32) || defined(__WIN32__) || defined(_WIN32) || \
	defined(_MSC_VER) || defined(__MINGW32__)
/**
 * A preprocessor macro that is only defined if compiling for Windows.
 */
#define CSVEE_PLATFORM_IS_WINDOWS 1
/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */
#define CSVEE_PLATFORM_NAME_IS "Windows"
#else
/**
 * A preprocessor macro that is only defined if compiling for others.
 */
#define CSVEE_PLATFORM_IS_OTHERS 1
/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */
#define CSVEE_PLATFORM_NAME_IS "Others"
#endif

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Compiler
//-----------------------------------------------------------------------------

/**
 * @defgroup compiler Compiler Definitions
 * @{
 */

/**
 * @brief   Checks if the compiler is of given brand.
 * @param   name  Compiler brand, like `MSVC`.
 * @retval  true   It is.
 * @retval  false  It isn't.
 */
#define CSVEE_COMPILER_IS(name) CSVEE_COMPILER_IS_##name

/// Compiler is apple
#if !defined(__clang__)
#define CSVEE_COMPILER_IS_APPLE 0
#elif !defined(__apple_build_version__)
#define CSVEE_COMPILER_IS_APPLE 0
#else
#define CSVEE_COMPILER_IS_APPLE 1
#define CSVEE_COMPILER_VERSION_MAJOR __clang_major__
#define CSVEE_COMPILER_VERSION_MINOR __clang_minor__
#define CSVEE_COMPILER_VERSION_PATCH __clang_patchlevel__
#endif

/// Compiler is clang
#if !defined(__clang__)
#define CSVEE_COMPILER_IS_CLANG 0
#elif CSVEE_COMPILER_IS(APPLE)
#define CSVEE_COMPILER_IS_CLANG 0
#else
#define CSVEE_COMPILER_IS_CLANG 1
#define CSVEE_COMPILER_VERSION_MAJOR __clang_major__
#define CSVEE_COMPILER_VERSION_MINOR __clang_minor__
#define CSVEE_COMPILER_VERSION_PATCH __clang_patchlevel__
#endif

/// Compiler is intel
#if !defined(__INTEL_COMPILER)
#define CSVEE_COMPILER_IS_INTEL 0
#elif !defined(__INTEL_COMPILER_UPDATE)
#define CSVEE_COMPILER_IS_INTEL 1
/* __INTEL_COMPILER = XXYZ */
#define CSVEE_COMPILER_VERSION_MAJOR (__INTEL_COMPILER / 100)
#define CSVEE_COMPILER_VERSION_MINOR (__INTEL_COMPILER % 100 / 10)
#define CSVEE_COMPILER_VERSION_PATCH (__INTEL_COMPILER % 10)
#else
#define CSVEE_COMPILER_IS_INTEL 1
/* __INTEL_COMPILER = XXYZ */
#define CSVEE_COMPILER_VERSION_MAJOR (__INTEL_COMPILER / 100)
#define CSVEE_COMPILER_VERSION_MINOR (__INTEL_COMPILER % 100 / 10)
#define CSVEE_COMPILER_VERSION_PATCH __INTEL_COMPILER_UPDATE
#endif

/// Compiler is msc
#if !defined(_MSC_VER)
#define CSVEE_COMPILER_IS_MSVC 0
#elif CSVEE_COMPILER_IS(CLANG)
#define CSVEE_COMPILER_IS_MSVC 0
#elif CSVEE_COMPILER_IS(INTEL)
#define CSVEE_COMPILER_IS_MSVC 0
#elif _MSC_VER >= 1400
#define CSVEE_COMPILER_IS_MSVC 1
/* _MSC_FULL_VER = XXYYZZZZZ */
#define CSVEE_COMPILER_VERSION_MAJOR (_MSC_FULL_VER / 10000000)
#define CSVEE_COMPILER_VERSION_MINOR (_MSC_FULL_VER % 10000000 / 100000)
#define CSVEE_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 100000)
#elif defined(_MSC_FULL_VER)
#define CSVEE_COMPILER_IS_MSVC 1
/* _MSC_FULL_VER = XXYYZZZZ */
#define CSVEE_COMPILER_VERSION_MAJOR (_MSC_FULL_VER / 1000000)
#define CSVEE_COMPILER_VERSION_MINOR (_MSC_FULL_VER % 1000000 / 10000)
#define CSVEE_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 10000)
#else
#define CSVEE_COMPILER_IS_MSVC 1
/* _MSC_VER = XXYY */
#define CSVEE_COMPILER_VERSION_MAJOR (_MSC_VER / 100)
#define CSVEE_COMPILER_VERSION_MINOR (_MSC_VER % 100)
#define CSVEE_COMPILER_VERSION_PATCH 0
#endif

/// Compiler is gcc
#if !defined(__GNUC__)
#define CSVEE_COMPILER_IS_GCC 0
#elif CSVEE_COMPILER_IS(APPLE)
#define CSVEE_COMPILER_IS_GCC 0
#elif CSVEE_COMPILER_IS(CLANG)
#define CSVEE_COMPILER_IS_GCC 0
#elif CSVEE_COMPILER_IS(INTEL)
#define CSVEE_COMPILER_IS_GCC 0
#else
#define CSVEE_COMPILER_IS_GCC 1
#define CSVEE_COMPILER_VERSION_MAJOR __GNUC__
#define CSVEE_COMPILER_VERSION_MINOR __GNUC_MINOR__
#define CSVEE_COMPILER_VERSION_PATCH __GNUC_PATCHLEVEL__
#endif

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Warnings
//-----------------------------------------------------------------------------

/**
 * @defgroup compiler Compiler Warnings
 * @{
 */

#if CSVEE_COMPILER_IS(CLANG)
#define CSVEE_PRAGMA_TO_STR(x) _Pragma(#x)
#define CSVEE_CLANG_SUPPRESS_WARNING_PUSH _Pragma("clang diagnostic push")
#define CSVEE_CLANG_SUPPRESS_WARNING(w) \
	CSVEE_PRAGMA_TO_STR(clang diagnostic ignored w)
#define CSVEE_CLANG_SUPPRESS_WARNING_POP _Pragma("clang diagnostic pop")
#define CSVEE_CLANG_SUPPRESS_WARNING_WITH_PUSH(w) \
	CSVEE_CLANG_SUPPRESS_WARNING_PUSH CSVEE_CLANG_SUPPRESS_WARNING(w)
#else // CSVEE_CLANG
#define CSVEE_CLANG_SUPPRESS_WARNING_PUSH
#define CSVEE_CLANG_SUPPRESS_WARNING(w)
#define CSVEE_CLANG_SUPPRESS_WARNING_POP
#define CSVEE_CLANG_SUPPRESS_WARNING_WITH_PUSH(w)
#endif // CSVEE_CLANG

#if CSVEE_COMPILER_IS(GCC)
#define CSVEE_PRAGMA_TO_STR(x) _Pragma(#x)
#define CSVEE_GCC_SUPPRESS_WARNING_PUSH _Pragma("GCC diagnostic push")
#define CSVEE_GCC_SUPPRESS_WARNING(w) \
	CSVEE_PRAGMA_TO_STR(GCC diagnostic ignored w)
#define CSVEE_GCC_SUPPRESS_WARNING_POP _Pragma("GCC diagnostic pop")
#define CSVEE_GCC_SUPPRESS_WARNING_WITH_PUSH(w) \
	CSVEE_GCC_SUPPRESS_WARNING_PUSH CSVEE_GCC_SUPPRESS_WARNING(w)
#else // CSVEE_GCC
#define CSVEE_GCC_SUPPRESS_WARNING_PUSH
#define CSVEE_GCC_SUPPRESS_WARNING(w)
#define CSVEE_GCC_SUPPRESS_WARNING_POP
#define CSVEE_GCC_SUPPRESS_WARNING_WITH_PUSH(w)
#endif // CSVEE_GCC

#if CSVEE_COMPILER_IS(MSVC)
#define CSVEE_MSVC_SUPPRESS_WARNING_PUSH __pragma(warning(push))
#define CSVEE_MSVC_SUPPRESS_WARNING(w) __pragma(warning(disable : w))
#define CSVEE_MSVC_SUPPRESS_WARNING_POP __pragma(warning(pop))
#define CSVEE_MSVC_SUPPRESS_WARNING_WITH_PUSH(w) \
	CSVEE_MSVC_SUPPRESS_WARNING_PUSH CSVEE_MSVC_SUPPRESS_WARNING(w)
#else // CSVEE_MSVC
#define CSVEE_MSVC_SUPPRESS_WARNING_PUSH
#define CSVEE_MSVC_SUPPRESS_WARNING(w)
#define CSVEE_MSVC_SUPPRESS_WARNING_POP
#define CSVEE_MSVC_SUPPRESS_WARNING_WITH_PUSH(w)
#endif // CSVEE_MSVC

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Import/Export
//-----------------------------------------------------------------------------

/**
 * @defgroup export Export Definitions
 * @{
 */

#if defined(_WIN32)
#define CSVEE_NO_EXPORT_ATTR
#define CSVEE_API_EXPORT __declspec(dllexport)
#define CSVEE_API_IMPORT __declspec(dllimport)
#define CSVEE_DEPRECATED_ATTR __declspec(deprecated)
#else // _WIN32
#define CSVEE_API_EXPORT __attribute__((visibility("default")))
#define CSVEE_API_IMPORT __attribute__((visibility("default")))
#define CSVEE_NO_EXPORT_ATTR __attribute__((visibility("hidden")))
#define CSVEE_DEPRECATED_ATTR __attribute__((__deprecated__))
#endif // _WIN32

/**
 * @def CSVEE_API
 * @brief Macro for public API symbol export/import.
 * @details Use this macro to annotate all public API functions for correct
 * symbol visibility on all platforms.
 */

#if defined(CSVEE_BUILD_STATIC)
#define CSVEE_API
#elif defined(CSVEE_BUILD_SHARED)
/* We are building this library */
#define CSVEE_API CSVEE_API_EXPORT
#elif defined(CSVEE_IMPORT)
/* We are using this library */
#define CSVEE_API CSVEE_API_IMPORT
#else // CSVEE_BUILD_STATIC
#define CSVEE_API
#endif // CSVEE_BUILD_STATIC

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Data Structures
//-----------------------------------------------------------------------------

/**
 * @defgroup basic Basic Types
 * @brief Core types and data structures for Argparser.
 * @{
 */

typedef enum CsvError_t
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
	NULL_FILE,	  // if pointer is null
	FILE_ERROR,
	IO_ERROR,
	VALUE_NULL,
	WRONG_CAST,
	VALUE_NULL,
	WRONG_CAST,
	PARSE_ERROR,
	OUT_OF_MEMORY,

} CsvError_t;

typedef enum CSVQuoteType
{
	CSVEE_QUOTE_ALL,
	CSVEE_QUOTE_NONE,
	CSVEE_QUOTE_STRING,
	CSVEE_QUOTE_NOTNULL,
	CSVEE_QUOTE_MINIMAL,
	CSVEE_QUOTE_NONNUMERIC,

} CSVQuoteType;

typedef enum CSVValueType
{
	CSVEE_UNKNOW_VALUE,
	CSVEE_NULL_VALUE,	 /**< Empty string */
	CSV_BOOL_VALUE,		 /**< Boolean value */
	CSV_DOUBLE_VALUE,	 /**< Floating point value */
	CSVEE_STRING_VALUE,	 /**< Non-numeric string */
	CSVEE_INTEGER_VALUE, /**< Integer value */

} CSVValueType;

// Define a structure for a CSV field
typedef struct CSVDialect_t
{
	CSVQuoteType quoting;

	char *name;

	char delimiter;
	char quotechar;

	char *lineterminator;

	bool doublequote;
	bool skipwhitespace;

} CSVDialect_t;

// Define a structure for a CSV field
typedef struct CSVField_t
{
	struct CSVField_t *prev;
	struct CSVField_t *next;
	CSVValueType type;

	union
	{
		int _integer;
		char *_string;
		bool _boolean;
		double _double;

	} value;

} CSVField_t;

// Define a structure for a CSV row
typedef struct CSVRow_t
{
	struct CSVRow_t *prev;
	struct CSVRow_t *next;

	CSVField_t *fields;
	size_t count;

} CSVRow_t;

typedef struct CsvIterator_t
{
	const CSVRow_t *ptr;
} CsvIterator_t;

typedef struct RowIterator_t
{
	const CSVField_t *ptr;
} RowIterator_t;

// Define a structure for a CSV file
typedef struct Csvee_t
{
	CSVDialect_t dialect;
	CSVRow_t *rows;
	size_t count;
	size_t size;
	char sep;
} Csvee_t;

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] C Only Functions
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

	RowIterator_t csv_row_iter_begin(const CSVRow_t *row);
	RowIterator_t csv_row_iter_end(const CSVRow_t *row);

	void csv_row_iter_next(RowIterator_t *row_iter);
	char *csv_row_iter_peek(RowIterator_t *row_iter);
	bool csv_row_iter_equal(RowIterator_t *begin_iter, RowIterator_t *end_iter);

	CsvIterator_t csv_csv_iter_begin(const Csvee_t *csvee);
	CsvIterator_t csv_csv_iter_end(const Csvee_t *csvee);

	void csv_csv_iter_next(CsvIterator_t *csv_iter);
	const CSVRow_t *csv_csv_iter_peek(CsvIterator_t *csv_iter);
	bool csv_csv_iter_equal(CsvIterator_t *begin_iter, CsvIterator_t *end_iter);

	void csv_row_iter_next(RowIterator_t *row_iter);
	char *csv_row_iter_peek(RowIterator_t *row_iter);
	bool csv_row_iter_equal(RowIterator_t *begin_iter, RowIterator_t *end_iter);

	double csv_field_to_double(CSVField_t *field);
	int csv_field_to_integer(CSVField_t *field);
	char *csv_field_to_string(CSVField_t *field);
	int csv_field_to_boolean(CSVField_t *field);

	CSVField_t csvee_create_field(const char *value);
	CSVField_t csvee_get_filed(Csvee_t *csvee, size_t row, size_t col);

	CSVRow_t csvee_create_row(size_t field_count);
	CSVRow_t csvee_get_row(Csvee_t *csvee, size_t row);

	Csvee_t csvee_create_csv(char sep);
	Csvee_t csvee_copy_csv(const Csvee_t *file);

	int csvee_update_field(Csvee_t *csvee, size_t row, size_t col,
						   const char *value);
	int csvee_delete_field(Csvee_t *csvee, size_t row, size_t col);
	int csvee_field_exist(Csvee_t *csvee, size_t row, size_t col);
	int csvee_field_equal(CSVField_t *field, CSVField_t *other);

	int csvee_add_row(Csvee_t *csvee, size_t fields_count, ...);
	int csvee_update_row(Csvee_t *csvee, size_t row, size_t fields_count, ...);
	int csvee_delete_row(Csvee_t *csvee, size_t row);
	int csvee_row_exist(Csvee_t *csvee, size_t row);
	int csvee_row_equal(CSVRow_t *row, CSVRow_t *other);

	Csvee_t csvee_read_from_file(const char *filename);
	bool csvee_write_to_file(const Csvee_t *csvee, const char *filename);

	void csvee_error(CsvError_t error, const char *format, ...);
	const char *csvee_error_name(CsvError_t error);

	void csvee_field_str(const CSVField_t *field, char **buffer, size_t *size);
	void csvee_row_str(const CSVRow_t *row, char sep, char **buffer, size_t *size);
	void csvee_csv_str(const Csvee_t *csvee, char **buffer, size_t *size);

	void csvee_free_row(CSVRow_t *row);
	void csvee_free_csv(Csvee_t *csvee);
	void csvee_free_field(CSVField_t *field);

#ifdef __cplusplus
}
#endif //__cplusplus

//-----------------------------------------------------------------------------
// [SECTION] C++ Only Classes
//-----------------------------------------------------------------------------

#ifdef __cplusplus

namespace csvee
{
	class CSVField
	{
	public:
		CSVField() = default;

		CSVField(CSVField_t field);
		CSVField(std::string field);
		CSVField(std::string_view field);

		operator std::string() const;

		CSVValueType type();

		bool is_int();
		bool is_num();
		bool is_bool();
		bool is_null();
		bool is_float();

	private:
		CSVField_t m_Field;
		std::string_view m_FieldSV;
	};

	class CSVRow
	{
	public:
		CSVRow() = default;

		CSVRow(std::vector<std::string> row);

		operator std::vector<std::string>() const;

		CSVField operator[](size_t n) const;
		CSVField operator[](const std::string &) const;

	private:
		CSVRow_t m_Row;
	};

	template <class CSVDialect>
	class Csvee
	{
	public:
		Csvee();

		dialect Dialect();

		Csvee *WriteHead();
		Csvee *WriteRow();
		Csvee *WriteRows();

		// CSV-level iterators for range-based for
		CsvIterator_t begin() const { return csv_csv_iter_begin(&m_file); }
		CsvIterator_t end() const { return csv_csv_iter_end(&m_file); }

		// Row-level helpers
		static RowIterator_t row_begin(const CSVRow_t *row) { return csv_row_iter_begin(row); }
		static RowIterator_t row_end(const CSVRow_t *row) { return csv_row_iter_end(row); }

	private:
		using dialect = CSVDialect;

	private:
		dialect m_Dialect;
		Csvee_t m_Csvee;
	};

	class CSVDialect
	{
	public:
		CSVDialect(char *name, char delimiter, char quotechar, char *lineterminator, bool doublequote, bool skipwhitespace, CSVQuoteType quoting);
		CSVDialect(std::string name, char delimiter, char quotechar, std::string lineterminator, bool doublequote, bool skipwhitespace, CSVQuoteType quoting);

	private:
		CSVDialect_t m_Dialect;
	};

	class Excel : public CSVDialect
	{
	public:
		Excel()
			: CSVDialect("excel", ',', '"', "\r\n", true, false, CSVEE_QUOTE_MINIMAL) {};
	};

	class ExcelTab : public CSVDialect
	{
	public:
		ExcelTab()
			: CSVDialect("excel-tab", '\t', '"', "\r\n", true, false, CSVEE_QUOTE_MINIMAL) {};
	};

	class Unix : public CSVDialect
	{
	public:
		Unix()
			: CSVDialect("unix", ',', '"', "\n", true, false, CSVEE_QUOTE_ALL) {};
	};

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
		CsveeError(CsvError_t type);

		/**
		 * @brief Constructs an exception with a specific message and error type.
		 * @param message The error message.
		 * @param type The type of the error.
		 */
		CsveeError(const std::string &message, CsvError_t type);

		/**
		 * @brief Gets the error message.
		 * @return The error message.
		 */
		const char *what() const noexcept override;

		/**
		 * @brief Gets the error type.
		 * @return The error type.
		 */
		CsvError_t GetErrType() const noexcept;

		/**
		 * @brief Gets the name of the error type.
		 * @param error The error type.
		 * @return The name of the error type.
		 */
		std::string GetErrName(CsvError_t error) const noexcept;

	private:
		mutable std::string m_Msg; //!< The error message.
		CsvError_t m_ErrType;	   //!< The error type.
	};

	template <class CSVDialect, class OutputType>
	void writer(Csvee<CSVDialect> &csvee, OutputType csv_output);

	template <class CSVDialect, class InputType>
	Csvee<CSVDialect> reader(InputType csv_input);

}; // namespace csvee

#endif //__cplusplus

#endif // DJOEZEKE_CSVEE_H

#ifdef CSVEE_IMPLEMENTATION

#pragma region Internal

//-----------------------------------------------------------------------------
// [SECTION] Defines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] Data Structures
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] C Only Functions
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	//-----------------------------------------------------------------------------
	// [SECTION] Declarations
	//-----------------------------------------------------------------------------

	//-----------------------------------------------------------------------------
	// [SECTION] Definations
	//-----------------------------------------------------------------------------

#ifdef __cplusplus
};
#endif // __cplusplus

//-----------------------------------------------------------------------------
// [SECTION] C++ Only Classes
//-----------------------------------------------------------------------------

#ifdef __cplusplus

//-----------------------------------------------------------------------------
// [SECTION] Declarations
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] Definations
//-----------------------------------------------------------------------------

#endif //__cplusplus

#pragma endregion

#pragma region Csvee

//-----------------------------------------------------------------------------
// [SECTION] C Only Functions
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	RowIterator_t csv_row_iter_begin(const CSVRow_t *row)
	{
		RowIterator_t iter;
		if (row == NULL || row->count == 0)
		{
			iter.ptr = NULL;
		}
		else
		{
			iter.ptr = &row->fields[0];
		}
		return iter;
	};

	RowIterator_t csv_row_iter_end(const CSVRow_t *row)
	{
		(void)row;
		RowIterator_t iter;
		iter.ptr = NULL;
		return iter;
	};

	void csv_row_iter_next(RowIterator_t *row_iter)
	{
		if (row_iter == NULL)
		{
			return;
		}
		if (row_iter->ptr != NULL)
			row_iter->ptr++;
	};

	char *csv_row_iter_peek(RowIterator_t *row_iter)
	{
		if (row_iter == NULL || row_iter->ptr == NULL)
			return NULL;
		return row_iter->ptr->value;
	};

	bool csv_row_iter_equal(RowIterator_t *begin_iter, RowIterator_t *end_iter)
	{
		return (begin_iter->ptr == end_iter->ptr);
	};

	CsvIterator_t csv_csv_iter_begin(const Csvee_t *csvee)
	{
		CsvIterator_t iter;
		if (csvee == NULL || csvee->count == 0)
		{
			iter.ptr = NULL;
		}
		else
		{
			iter.ptr = &csvee->rows[0];
		}
		return iter;
	};

	CsvIterator_t csv_csv_iter_end(const Csvee_t *csvee)
	{
		(void)csvee;
		CsvIterator_t iter;
		iter.ptr = NULL;
		return iter;
	};

	void csv_csv_iter_next(CsvIterator_t *csv_iter)
	{
		if (csv_iter == NULL)
			return;
		if (csv_iter->ptr != NULL)
			csv_iter->ptr++;
	};

	const CSVRow_t *csv_csv_iter_peek(CsvIterator_t *csv_iter)
	{
		if (csv_iter == NULL || csv_iter->ptr == NULL)
			return NULL;
		return csv_iter->ptr;
	};

	bool csv_csv_iter_equal(CsvIterator_t *begin_iter, CsvIterator_t *end_iter)
	{
		return (begin_iter->ptr == end_iter->ptr);
	};

	double csv_field_to_double(CSVField_t *field)
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

	int csv_field_to_integer(CSVField_t *field)
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

	char *csv_field_to_string(CSVField_t *field)
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

	int csv_field_to_boolean(CSVField_t *field)
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
	CSVField_t csvee_create_field(const char *value)
	{
		CSVField_t field;
		field.value = strdup(value);
		return field;
	}

	CSVField_t csvee_get_filed(Csvee_t *csvee, size_t row, size_t col)
	{
		CSVField_t field = csvee_create_field("");

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
	CSVRow_t csvee_create_row(size_t field_count)
	{
		CSVRow_t row;
		row.fields = (CSVField_t *)malloc(field_count * sizeof(CSVField_t));
		row.count = field_count;
		return row;
	}

	CSVRow_t csvee_get_row(Csvee_t *csvee, size_t row)
	{
		CSVRow_t nrow = csvee_create_row(0);

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
		file.rows = (CSVRow_t *)malloc(file.size * sizeof(CSVRow_t));
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

	int csvee_update_field(Csvee_t *csvee, size_t row, size_t col,
						   const char *value)
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

	int csvee_field_equal(CSVField_t *field, CSVField_t *other)
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
			csvee->rows = (CSVRow_t *)realloc(csvee->rows, csvee->size * sizeof(CSVRow_t));
		}

		csvee->rows[csvee->count] = csvee_create_row(fields_count);

		// Loop through all the arguments
		for (size_t i = 0; i < fields_count; i++)
		{
			csvee->rows[csvee->count].fields[i] =
				csvee_create_field(va_arg(args, const char *));
		}

		csvee->count++;

		// Clean up the argument list
		va_end(args);
		return 0;
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

	int csvee_row_equal(CSVRow_t *row, CSVRow_t *other)
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
		Csvee_t csvee = csvee_create_csv(CSVEE_SEPERATOR);

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

		// csvee.rows = (CSVRow_t *)malloc(csvee.size * sizeof(CSVRow_t));

		while (fgets(line, sizeof(line), file))
		{
			if (csvee.count >= csvee.size)
			{
				csvee.size *= 2;
				csvee.rows = (CSVRow_t *)realloc(csvee.rows, csvee.size * sizeof(CSVRow_t));
			}

			CSVRow_t row = csvee_create_row(col_capacity);
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
						row.fields =
							(CSVField_t *)realloc(row.fields, col_capacity * sizeof(CSVField_t));
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

	void csvee_error(CsvError_t error, const char *format, ...)
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

	const char *csvee_error_name(CsvError_t error)
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

	void csvee_field_str(const CSVField_t *field, char **buffer, size_t *size)
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

	void csvee_row_str(const CSVRow_t *row, char sep, char **buffer, size_t *size)
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
			csvee_row_str(&file->rows[i], file->sep, buffer, size);
		}
	}

	void csvee_free_field(CSVField_t *field) { free(field->value); }

	void csvee_free_row(CSVRow_t *row)
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
};
#endif // __cplusplus

//-----------------------------------------------------------------------------
// [SECTION] C++ Only Classes
//-----------------------------------------------------------------------------

#ifdef __cplusplus

namespace csvee
{
	CSVDialect::CSVDialect(char *name, char delimiter, char quotechar, char *lineterminator, bool doublequote, bool skipwhitespace, CSVQuoteType quoting)
	{
		m_Dialect.name = name;
		m_Dialect.quoting = quoting;
		m_Dialect.delimiter = delimiter;
		m_Dialect.quotechar = quotechar;
		m_Dialect.doublequote = doublequote;
		m_Dialect.lineterminator = lineterminator;
		m_Dialect.skipwhitespace = skipwhitespace;
	};

	CSVDialect::CSVDialect(std::string name, char delimiter, char quotechar, std::string lineterminator, bool doublequote, bool skipwhitespace, CSVQuoteType quoting)
	{
		m_Dialect.name = const_cast<char *>(name.c_str());
		m_Dialect.quoting = quoting;
		m_Dialect.delimiter = delimiter;
		m_Dialect.quotechar = quotechar;
		m_Dialect.doublequote = doublequote;
		m_Dialect.lineterminator = const_cast<char *>(lineterminator.c_str());
		m_Dialect.skipwhitespace = skipwhitespace;
	};

	CsveeError::CsveeError()
	{
		m_ErrType = UNKNOWN;
		m_Msg = std::string("(") + GetErrName(UNKNOWN) + std::string(") -> ") +
				std::string("UNKNOWN ERROR TYPE");
	};

	CsveeError::CsveeError(CsvError_t errorType)
	{
		m_ErrType = errorType;
		m_Msg = std::string("(") + GetErrName(errorType) + std::string(") -> ") +
				std::string("ERROR MESSAGE EMPTY");
	};

	CsveeError::CsveeError(const std::string &message, CsvError_t errorType)
	{
		m_ErrType = errorType;
		m_Msg =
			std::string("(") + GetErrName(errorType) + std::string(") -> ") + message;
	};

	const char *CsveeError::what() const noexcept { return m_Msg.c_str(); };

	CsvError_t CsveeError::GetErrType() const noexcept { return m_ErrType; };

	std::string CsveeError::GetErrName(CsvError_t error) const noexcept
	{
		std::string name = csvee_error_name(error);
		return name;
	};

} // namespace csvee

#endif //__cplusplus

#pragma endregion // Csvee

#endif // CSVEE_IMPLEMENTATION
