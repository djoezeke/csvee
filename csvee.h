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
#include <iterator>
#include <memory>
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
	CSV_BOOL_VALUE,	  /**< Boolean value */
	CSVEE_NULL_VALUE, /**< Empty string */
	CSV_DOUBLE_VALUE, /**< Floating point value */
	CSVEE_UNKNOW_VALUE,
	CSVEE_STRING_VALUE,	 /**< Non-numeric string */
	CSVEE_INTEGER_VALUE, /**< Integer value */

} CSVValueType;

typedef struct CSVStat_t
{
} CSVStat_t;

typedef struct CSVInfo_t
{
	size_t rows;
	char *filename;
	size_t columns;

} CSVInfo_t;

typedef struct CSVDialect_t
{
	char *name;

	char delimiter;
	char quotechar;
	char lineterminator;

	bool doublequote;
	bool skipwhitespace;

	CSVQuoteType quoting;

} CSVDialect_t;

typedef struct CSVField_t
{

	CSVValueType type;

	union
	{
		int _integer;
		char *_string;
		bool _boolean;
		double _double;

	} value;

} CSVField_t;

typedef struct CSVRow_t
{
	CSVField_t *fields;
	size_t count;

} CSVRow_t;

typedef struct Csvee_t
{
	CSVDialect_t *dialect;
	CSVRow_t *rows;
	size_t count;
	size_t size;

} Csvee_t;

typedef struct CsvIterator_t
{
	const CSVRow_t *ptr;
} CsvIterator_t;

typedef struct RowIterator_t
{
	const CSVField_t *ptr;
} RowIterator_t;

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] C Only Functions
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

	void csvee_init(Csvee_t *csvee, CSVDialect_t *dialect);
	void csvee_free(Csvee_t *csvee);

	CSVRow_t *csv_next_row(const Csvee_t *csvee);
	CSVField_t *csv_next_field(const CSVRow_t *row);

	RowIterator_t *csv_row_iter_begin(const CSVRow_t *row);
	RowIterator_t *csv_row_iter_end(const CSVRow_t *row);

	void csv_row_iter_next(RowIterator_t *row_iter);
	const CSVField_t *csv_row_iter_peek(RowIterator_t *row_iter);
	bool csv_row_iter_equal(RowIterator_t *begin_iter, RowIterator_t *end_iter);

	CsvIterator_t *csv_csv_iter_begin(const Csvee_t *csvee);
	CsvIterator_t *csv_csv_iter_end(const Csvee_t *csvee);

	void csv_csv_iter_next(CsvIterator_t *csv_iter);
	const CSVRow_t *csv_csv_iter_peek(CsvIterator_t *csv_iter);
	bool csv_csv_iter_equal(CsvIterator_t *begin_iter, CsvIterator_t *end_iter);

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

	Csvee_t *csvee_read_from_file(const char *filename);
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

	template <class Csvee>
	class CsveeIterator
	{
	public:
		using ValueType = CSVRow;
		using DifferenceType = size_t;
		using PointerType = ValueType *;
		using ConstPointerType = const ValueType *;
		using ReferenceType = ValueType &;
		using ConstReferenceType = const ValueType &;

	public:
		CsveeIterator(PointerType ptr);
		CsveeIterator(const PointerType ptr);

		PointerType operator->() const;
		ReferenceType operator*() const;
		ReferenceType operator[](size_t index);

		CsveeIterator &operator++();
		CsveeIterator operator++(int);

		CsveeIterator &operator--();
		CsveeIterator operator--(int);

		CsveeIterator operator+(DifferenceType n) const;
		CsveeIterator operator-(DifferenceType n) const;

		bool operator==(const CsveeIterator &other) const noexcept;
		bool operator!=(const CsveeIterator &other) const noexcept;

	private:
		PointerType m_Ptr;
	};

	class CSVRowIterator
	{
	public:
		using ValueType = CSVField;
		using DifferenceType = size_t;
		using PointerType = ValueType *;
		using ConstPointerType = const ValueType *;
		using ReferenceType = ValueType &;
		using ConstReferenceType = const ValueType &;

	public:
		CSVRowIterator(PointerType ptr);
		CSVRowIterator(const PointerType ptr);

		PointerType operator->() const;
		ReferenceType operator*() const;
		ReferenceType operator[](size_t index);

		CSVRowIterator &operator++();
		CSVRowIterator operator++(int);

		CSVRowIterator &operator--();
		CSVRowIterator operator--(int);

		CSVRowIterator operator+(DifferenceType n) const;
		CSVRowIterator operator-(DifferenceType n) const;

		bool operator==(const CSVRowIterator &other) const noexcept;
		bool operator!=(const CSVRowIterator &other) const noexcept;

	private:
		PointerType m_Ptr;
	};

	class CSVRow
	{
	public:
		using SizeType = size_t;
		using ValueType = CSVField;
		using PointerType = ValueType *;
		using ReferenceType = ValueType &;
		using ConstPointerType = const PointerType;
		using ConstReferenceType = const ReferenceType;

		using Iterator = CSVRowIterator;
		using ConstIterator = const Iterator;
		using ReverseIterator = std::reverse_iterator<Iterator>;
		using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	public:
		CSVRow() = default;

		CSVRow(std::vector<std::string> row);

		operator std::vector<std::string>() const;

		Iterator begin() const;
		Iterator end() const noexcept;

		ReverseIterator rend() const;
		ReverseIterator rbegin() const noexcept;

		CSVField operator[](SizeType n) const;
		CSVField operator[](const std::string &) const;

	private:
		CSVRow_t m_Row;
	};

	template <class CSVDialect>
	class Csvee
	{
	private:
		using Dialect = CSVDialect;

		template <class OutputStream>
		using Writer = CsveeWriter<OutputStream, Dialect>;

		template <class InputStream>
		using Reader = CsveeReader<InputStream, Dialect>;

	public:
		using Iterator = CsveeIterator<Csvee<Dialect>>;
		using ConstIterator = const Iterator;
		using ReverseIterator = std::reverse_iterator<Iterator>;
		using ConstReverseIterator = const ReverseIterator;

	public:
		Csvee();

		Dialect dialect();

		template <typename... T>
		CsveeWriter &WriteHead(const std::vector<T> &record);

		template <typename... T, size_t Size>
		CsveeWriter &WriteHead(const std::array<T, Size> &record);

		template <typename... T>
		Csvee<Dialect> *WriteRow(const std::vector<T> &record);

		template <typename... T, size_t Size>
		Csvee<Dialect> *WriteRow(const std::array<T, Size> &record);

		Csvee<Dialect> *operator<<(const Csvee<CSVDialect> &csvee);

		Iterator begin() const;
		Iterator end() const noexcept;

		ReverseIterator rend() const;
		ReverseIterator rbegin() const noexcept;

	private:
		Dialect m_Dialect;
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

	template <class InputStream, class CSVDiaect>
	class CsveeReader
	{
	public:
		CsveeReader(InputStream &stream, CSVDialect &dialect);

		CsveeReader(const CsveeReader &) = delete;
		CsveeReader &operator=(const CsveeReader &) = delete;

		CsveeReader(CsveeReader &&) = default;
		CsveeReader &operator=(CsveeReader &&other) = default;

		Iterator begin() const;
		Iterator end() const noexcept;

		ReverseIterator rend() const;
		ReverseIterator rbegin() const noexcept;

	public:
		using Iterator = CsveeIterator<CSVDialect>;
		using ReverseIterator = std::reverse_iterator<Iterator>;

	private:
		InputStream &m_Input;
	};

	template <class OutputStream, class CSVDiaect>
	class CsveeWriter
	{
	public:
		CsveeWriter(OutputStream &stream, CSVDialect &dialect);

		CsveeWriter(const CsveeWriter &) = delete;
		CsveeWriter &operator=(const CsveeWriter &) = delete;

		CsveeWriter(CsveeWriter &&) = default;
		CsveeWriter &operator=(CsveeWriter &&other) = default;

		template <typename T>
		CsveeWriter &WriteHead(const std::vector<T> &record);

		template <typename T, size_t Size>
		CsveeWriter &WriteHead(const std::array<T, Size> &record);

		template <typename T>
		CsveeWriter &WriteRow(const std::vector<T> &record);

		template <typename T, size_t Size>
		CsveeWriter &WriteRow(const std::array<T, Size> &record);

		template <typename T>
		CsveeWriter &operator<<(const std::vector<T> &record);

		template <typename T, size_t Size>
		CsveeWriter &operator<<(const std::array<T, Size> &record);

		~CsveeWriter();

	private:
		OutputStream &m_Output;
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

	using csv = Csvee<Excel>;

	using tsv = Csvee<ExcelTab>;

	template <class InputStream>
	using CSVReader = CsveeReader<InputStream, Excel>;

	template <class InputStream>
	using TSVReader = CsveeReader<InputStream, ExcelTab>;

	template <class OutputStream>
	using CSVWriter = CsveeWriter<OutputStream, Excel>;

	template <class OutputStream>
	using TSVWriter = CsveeWriter<OutputStream, ExcelTab>;

	template <class OutputStream, class CSVDialect>
	CsveeWriter<OutputStream, CSVDialect> writer(OutputStream &output, CSVDialect dialect);

	template <class InputStream, class CSVDialect>
	CsveeWriter<InputStream, CSVDialect> reader(InputStream &intput, CSVDialect dialect);

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

	void csvee_dialect_init(CSVDialect_t *dialect, char *name, char delimeter, char quotechar, bool skipwhitespace, bool doublequote, CSVQuoteType quoting, char lineterminator)
	{
		if (dialect == NULL)
			return;

		/* copy/own the name and lineterminator so free() is safe later */
		if (name)
		{
			dialect->name = strdup(name);
		}
		else
		{
			dialect->name = NULL;
		}

		dialect->quoting = quoting;
		dialect->delimiter = delimeter;
		dialect->quotechar = quotechar;
		dialect->doublequote = doublequote;
		dialect->skipwhitespace = skipwhitespace;
		dialect->lineterminator = lineterminator;
	};

	void csvee_dialect_free(CSVDialect_t *dialect)
	{
		if (!dialect)
			return;
		if (dialect->name)
			free(dialect->name);
		free(dialect);
	};

	void csvee_init(Csvee_t *csvee, CSVDialect_t *dialect)
	{
		if (csvee == NULL)
			return;
		csvee->dialect = dialect;
		csvee->rows = NULL;
		csvee->count = 0;
		csvee->size = 1;
	};

	void csvee_free(Csvee_t *csvee)
	{
		for (size_t i = 0; i < csvee->count; i++)
		{
			csvee_free_row(&csvee->rows[i]);
		}
		csvee->count = 0;
		free(csvee->rows);
	};

	RowIterator_t *csv_row_iter_begin(const CSVRow_t *row)
	{
		RowIterator_t *iter = (RowIterator_t *)malloc(sizeof(RowIterator_t));
		if (!iter)
			return NULL;
		if (row == NULL || row->count == 0)
		{
			iter->ptr = NULL;
		}
		else
		{
			iter->ptr = &row->fields[0];
		}
		return iter;
	};

	RowIterator_t *csv_row_iter_end(const CSVRow_t *row)
	{
		(void)row;
		RowIterator_t *iter = (RowIterator_t *)malloc(sizeof(RowIterator_t));
		if (!iter)
			return NULL;
		iter->ptr = NULL;
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

	bool csv_row_iter_equal(RowIterator_t *begin_iter, RowIterator_t *end_iter)
	{
		return (begin_iter->ptr == end_iter->ptr);
	};

	CsvIterator_t *csv_csv_iter_begin(const Csvee_t *csvee)
	{
		CsvIterator_t *iter = (CsvIterator_t *)malloc(sizeof(CsvIterator_t));
		if (!iter)
			return NULL;
		if (csvee == NULL || csvee->count == 0)
		{
			iter->ptr = NULL;
		}
		else
		{
			iter->ptr = &csvee->rows[0];
		}
		return iter;
	};

	CsvIterator_t *csv_csv_iter_end(const Csvee_t *csvee)
	{
		(void)csvee;
		CsvIterator_t *iter = (CsvIterator_t *)malloc(sizeof(CsvIterator_t));
		if (!iter)
			return NULL;
		iter->ptr = NULL;
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

	/* Return first row (non-advancing helper). */
	CSVRow_t *csv_next_row(const Csvee_t *csvee)
	{
		if (csvee == NULL || csvee->count == 0)
			return NULL;
		return &csvee->rows[0];
	}

	/* Return first field of a row (non-advancing helper). */
	CSVField_t *csv_next_field(const CSVRow_t *row)
	{
		if (row == NULL || row->count == 0)
			return NULL;
		return &row->fields[0];
	}

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

	CSVField_t csvee_create_field(const char *value)
	{
		CSVField_t field;
		field.type = CSVEE_STRING_VALUE;
		field.value._string = strdup(value);
		return field;
	}

	/* Simple converter: return allocated string representing field value. */
	char *csv_field_to_string(CSVField_t *field)
	{
		if (field == NULL)
			return NULL;
		switch (field->type)
		{
		case CSVEE_STRING_VALUE:
			return strdup(field->value._string ? field->value._string : "");
		case CSVEE_INTEGER_VALUE:
		{
			char buf[64];
			snprintf(buf, sizeof(buf), "%d", field->value._integer);
			return strdup(buf);
		}
		case CSV_DOUBLE_VALUE:
		{
			char buf[128];
			snprintf(buf, sizeof(buf), "%g", field->value._double);
			return strdup(buf);
		}
		case CSV_BOOL_VALUE:
			return strdup(field->value._boolean ? "true" : "false");
		default:
			return strdup("");
		}
	}

	Csvee_t csvee_copy_csv(const Csvee_t *file)
	{
		Csvee_t copy = *file;
		copy.count = file->count;
		copy.rows = file->rows;
		copy.size = file->size;
		return copy;
	};

	Csvee_t *csvee_read_from_file(const char *filename)
	{
		if (!filename)
			return NULL;

		/* allocate csvee and dialect */
		Csvee_t *csvee = (Csvee_t *)malloc(sizeof(Csvee_t));
		if (!csvee)
			return NULL;

		CSVDialect_t *dialect = (CSVDialect_t *)malloc(sizeof(CSVDialect_t));
		if (!dialect)
		{
			free(csvee);
			return NULL;
		}

		/* choose delimiter based on extension */
		char del = CSVEE_SEPERATOR;
		size_t fnlen = strlen(filename);
		if (fnlen >= 4 && strcasecmp(filename + fnlen - 4, ".tsv") == 0)
			del = '\t';
		else if (fnlen >= 4 && strcasecmp(filename + fnlen - 4, ".txt") == 0)
			del = '\t';

		csvee_dialect_init(dialect, "excel", del, '"', true, true, CSVEE_QUOTE_MINIMAL, '\n');
		csvee_init(csvee, dialect);

		FILE *file = fopen(filename, "rb");
		if (!file)
		{
#ifdef CSVEE_DEBUG
			csvee_error(NULL_FILE, "Could not open file %s\n", filename);
#endif // CSVEE_DEBUG
			csvee_dialect_free(dialect);
			free(csvee);
			return NULL;
		}

		char line[MAX_LINE_LENGTH];
		size_t col_capacity = 8;

		csvee->rows = (CSVRow_t *)malloc(csvee->size * sizeof(CSVRow_t));
		if (!csvee->rows)
		{
			fclose(file);
			csvee_dialect_free(dialect);
			free(csvee);
			return NULL;
		}

		while (fgets(line, sizeof(line), file))
		{
			if (csvee->count >= csvee->size)
			{
				csvee->size *= 2;
				csvee->rows = (CSVRow_t *)realloc(csvee->rows, csvee->size * sizeof(CSVRow_t));
			}

			CSVRow_t row = csvee_create_row(col_capacity);
			char field[MAX_FIELD_LENGTH];
			size_t field_index = 0;
			size_t col_count = 0;
			bool in_quotes = false;

			size_t len = strlen(line);
			for (size_t i = 0; i < len; ++i)
			{
				char ch = line[i];
				if (ch == csvee->dialect->quotechar && (i == 0 || line[i - 1] != '\\'))
				{
					in_quotes = !in_quotes;
				}
				else if (ch == csvee->dialect->delimiter && !in_quotes)
				{
					field[field_index] = '\0';
					row.fields[col_count] = csvee_create_field(field);
					col_count++;
					field_index = 0;

					if (col_count >= col_capacity)
					{
						col_capacity *= 2;
						row.fields = (CSVField_t *)realloc(row.fields, col_capacity * sizeof(CSVField_t));
					}
				}
				else if (ch == '\r' || ch == '\n')
				{
					continue;
				}
				else
				{
					if (field_index + 1 < sizeof(field))
						field[field_index++] = ch;
				}
			}
			field[field_index] = '\0';
			row.fields[col_count] = csvee_create_field(field);
			col_count++;

			row.count = col_count;
			csvee->rows[csvee->count] = row;
			csvee->count++;
		}

		fclose(file);
		return csvee;
	}

	bool csvee_write_to_file(const Csvee_t *csvee, const char *filename)
	{
		if (!csvee || !filename)
			return false;

		FILE *file = fopen(filename, "wb");
		if (!file)
		{
#ifdef CSVEE_DEBUG
			csvee_error(NULL_FILE, "Could not open file %s for writing\n", filename);
#endif // CSVEE_DEBUG
			return false;
		}

		char delim = csvee->dialect ? csvee->dialect->delimiter : CSVEE_SEPERATOR;
		char quote = csvee->dialect ? csvee->dialect->quotechar : '"';
		bool doublequote = csvee->dialect ? csvee->dialect->doublequote : true;
		char lineterm = csvee->dialect ? csvee->dialect->lineterminator : '\n';

		for (size_t r = 0; r < csvee->count; ++r)
		{
			const CSVRow_t *row = &csvee->rows[r];
			for (size_t c = 0; c < row->count; ++c)
			{
				CSVField_t field = row->fields[c];
				char *s = csv_field_to_string(&field);
				bool need_quote = false;
				if (s)
				{
					for (char *p = s; *p; ++p)
					{
						if (*p == delim || *p == quote || *p == '\n' || *p == '\r')
						{
							need_quote = true;
							break;
						}
					}
				}

				if (need_quote)
					fputc(quote, file);

				if (s)
				{
					if (need_quote && doublequote)
					{
						/* write with doubled quotes */
						for (char *p = s; *p; ++p)
						{
							if (*p == quote)
							{
								fputc(quote, file);
								fputc(quote, file);
							}
							else
							{
								fputc(*p, file);
							}
						}
					}
					else if (s)
					{
						fputs(s, file);
					}
					free(s);
				}

				if (need_quote)
					fputc(quote, file);

				if (c + 1 < row->count)
					fputc(delim, file);
			}
			fputc(lineterm, file);
		}

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

	void csvee_free_field(CSVField_t *field)
	{

		switch (field->type)
		{
		case CSVEE_STRING_VALUE:
			free(field->value._string);
			break;

		default:
			break;
		};
		/* Do not free the field pointer itself because callers may pass pointers
			to elements inside an allocated array (e.g. &row->fields[i]).
			Reset contents instead. */
		field->value._string = NULL;
		field->type = CSVEE_NULL_VALUE;
	}

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
		if (!file)
		{
			return;
		}

		for (size_t i = 0; i < file->count; i++)
		{
			csvee_free_row(&file->rows[i]);
		}
		csvee_dialect_free(file->dialect);
		free(file->rows);
		file->count = 0;
		file->size = 0;
		free(file);
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
