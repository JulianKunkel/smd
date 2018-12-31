#ifndef HSMD_DERIVED_HEADER_H_
#define HSMD_DERIVED_HEADER_H_

#include <assert.h>
#include <string.h>

typedef enum smd_type_t{
	SMD_TYPE_UNKNOWN = 0,
	SMD_TYPE_INT8,
	SMD_TYPE_INT16,
	SMD_TYPE_INT32,
	SMD_TYPE_INT64,

	SMD_TYPE_UINT8,
	SMD_TYPE_UINT16,
	SMD_TYPE_UINT32,
	SMD_TYPE_UINT64,

	SMD_TYPE_FLOAT,			// if IEEE 754 (32bit)
	SMD_TYPE_DOUBLE,		// if IEEE 754 (64bit)

	SMD_TYPE_CHAR,		  	// 1 byte
	SMD_TYPE_STRING,
	SMD_TYPE_PRIMITIVE_END, // marker
	SMD_TYPE_ARRAY,
	SMD_TYPE_STRUCT,
	SMD_TYPE_DERIVED_END 		// marker
} smd_basic_type_t;

typedef struct smd_dtype_t smd_dtype_t;

typedef struct{
	uint64_t size;
	smd_dtype_t * type;
} smd_dtype_array_t;

typedef struct{
	int size;

  smd_dtype_t * type;
}smd_dtype_struct_t;

typedef struct{
	union {
		smd_dtype_array_t arr;
		smd_dtype_struct_t str;
	} u;
} smd_dtype_derived_t;

// derived data types
struct smd_dtype_t{
	smd_basic_type_t type;
	smd_dtype_derived_t specifier;
};

/**
 * Primitive datatypes
 */
extern smd_dtype_t * SMD_DTYPE_UNKNOWN;
extern smd_dtype_t * SMD_DTYPE_INT8;
extern smd_dtype_t * SMD_DTYPE_INT16;
extern smd_dtype_t * SMD_DTYPE_INT32;
extern smd_dtype_t * SMD_DTYPE_INT64;
extern smd_dtype_t * SMD_DTYPE_UINT8;
extern smd_dtype_t * SMD_DTYPE_UINT16;
extern smd_dtype_t * SMD_DTYPE_UINT32;
extern smd_dtype_t * SMD_DTYPE_UINT64;
extern smd_dtype_t * SMD_DTYPE_FLOAT;
extern smd_dtype_t * SMD_DTYPE_DOUBLE;
extern smd_dtype_t * SMD_DTYPE_CHAR;
extern smd_dtype_t * SMD_DTYPE_STRING;

/**
 *
 */
smd_dtype_t * smd_type_array(smd_dtype_t * base_type, uint64_t nmeb);

#endif
