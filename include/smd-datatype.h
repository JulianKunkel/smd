#ifndef HSMD_DERIVED_HEADER_H_
#define HSMD_DERIVED_HEADER_H_

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


typedef struct smd_string_stream_t smd_string_stream_t;

typedef enum smd_type_t {
  SMD_TYPE_AS_EXPECTED = -1,
  SMD_TYPE_UNKNOWN = 0,
  SMD_TYPE_INT8,
  SMD_TYPE_INT16,
  SMD_TYPE_INT32,
  SMD_TYPE_INT64,

  SMD_TYPE_UINT8,
  SMD_TYPE_UINT16,
  SMD_TYPE_UINT32,
  SMD_TYPE_UINT64,

  SMD_TYPE_FLOAT,  // if IEEE 754 (32bit)
  SMD_TYPE_DOUBLE, // if IEEE 754 (64bit)

  SMD_TYPE_CHAR, // 1 byte
  SMD_TYPE_STRING,
  SMD_TYPE_PRIMITIVE_END, // marker
  SMD_TYPE_EMPTY,
  SMD_TYPE_DTYPE,
  SMD_TYPE_ARRAY,
  SMD_TYPE_STRUCT,
  SMD_TYPE_EXTENT,
  SMD_TYPE_LB,
  SMD_TYPE_UB,
  SMD_TYPE_DERIVED_END // marker
} smd_basic_type_t;



typedef struct smd_dtype_t smd_dtype_t;

typedef struct {
  uint64_t count;
  smd_dtype_t *base;
} smd_dtype_array_t;

typedef struct {
  smd_dtype_t *base;
  size_t lb; // lower bound, indicates when the datatype starts
  //size_t ub; // upper bound, implicitly stored in extent
} smd_dtype_extent_t;

typedef struct {
  int size;
  const char **names;
  smd_dtype_t **types;
  size_t *offsets;
} smd_dtype_struct_t;

typedef struct {
  union {
    smd_dtype_array_t arr;
    smd_dtype_struct_t str;
    smd_dtype_extent_t ext;
  } u;
} smd_dtype_derived_t;

// derived data types
struct smd_dtype_t {
  int refcount;
  smd_basic_type_t type;
  uint64_t size;
  uint64_t extent;
  smd_dtype_derived_t specifier;
};

/**
 * Primitive datatypes
 */
extern smd_dtype_t *SMD_DTYPE_UNKNOWN;
extern smd_dtype_t *SMD_DTYPE_AS_EXPECTED;
extern smd_dtype_t *SMD_DTYPE_EMPTY;
extern smd_dtype_t *SMD_DTYPE_DTYPE;
extern smd_dtype_t *SMD_DTYPE_INT8;
extern smd_dtype_t *SMD_DTYPE_INT16;
extern smd_dtype_t *SMD_DTYPE_INT32;
extern smd_dtype_t *SMD_DTYPE_INT64;
extern smd_dtype_t *SMD_DTYPE_UINT8;
extern smd_dtype_t *SMD_DTYPE_UINT16;
extern smd_dtype_t *SMD_DTYPE_UINT32;
extern smd_dtype_t *SMD_DTYPE_UINT64;
extern smd_dtype_t *SMD_DTYPE_FLOAT;
extern smd_dtype_t *SMD_DTYPE_DOUBLE;
extern smd_dtype_t *SMD_DTYPE_CHAR;
extern smd_dtype_t *SMD_DTYPE_STRING;
extern smd_dtype_t *SMD_DTYPE_LB;
extern smd_dtype_t *SMD_DTYPE_UB;


#ifdef __cplusplus

template <class T>
inline smd_dtype_t* smd_c_to_smd_type(T & var){
  return SMD_DTYPE_UNKNOWN;
}

template <>
inline smd_dtype_t* smd_c_to_smd_type(int8_t & var){
  return SMD_DTYPE_INT8;
}

template <>
inline smd_dtype_t* smd_c_to_smd_type(int16_t & var){
  return SMD_DTYPE_INT16;
}

template <>
inline smd_dtype_t* smd_c_to_smd_type(int32_t & var){
  return SMD_DTYPE_INT32;
}

template <>
inline smd_dtype_t* smd_c_to_smd_type(int64_t & var){
  return SMD_DTYPE_INT64;
}

template <>
inline smd_dtype_t* smd_c_to_smd_type(uint8_t & var){
  return SMD_DTYPE_UINT8;
}

template <>
inline smd_dtype_t* smd_c_to_smd_type(uint16_t & var){
  return SMD_DTYPE_UINT16;
}

template <>
inline smd_dtype_t* smd_c_to_smd_type(uint32_t & var){
  return SMD_DTYPE_UINT32;
}

template <>
inline smd_dtype_t* smd_c_to_smd_type(uint64_t & var){
  return SMD_DTYPE_UINT64;
}

template <>
inline smd_dtype_t* smd_c_to_smd_type(float & var){
  return SMD_DTYPE_FLOAT;
}

template <>
inline smd_dtype_t* smd_c_to_smd_type(double & var){
  return SMD_DTYPE_DOUBLE;
}
#else
// no support in C++11
#define smd_c_to_smd_type(type) _Generic(type, \
  int8_t: SMD_DTYPE_INT8, \
  int16_t: SMD_DTYPE_INT16, \
  int32_t: SMD_DTYPE_INT32, \
  int64_t: SMD_DTYPE_INT64, \
  uint8_t: SMD_DTYPE_UINT8, \
  uint16_t: SMD_DTYPE_UINT16, \
  uint32_t: SMD_DTYPE_UINT32, \
  uint64_t: SMD_DTYPE_UINT64, \
  float: SMD_DTYPE_FLOAT, \
  double: SMD_DTYPE_DOUBLE \
)

#endif


#ifdef __cplusplus
extern "C" {
#endif

size_t smd_type_get_size(smd_dtype_t *type);
size_t smd_type_get_extent(smd_dtype_t *type);

/**
 *
 */
smd_dtype_t *smd_type_array(smd_dtype_t *base_type, uint64_t nmeb);

/**
 *
 */
smd_dtype_t *smd_type_extent(size_t lb, size_t ub, smd_dtype_t *base_type);

smd_dtype_t *smd_type_struct(int nmeb, size_t *offsets, size_t extent, char *const *names, smd_dtype_t **types);

/**
 * Decrement the reference counter by 1 and free the datatype if not further needed
 */
void smd_type_unref(smd_dtype_t **type);

#define smd_type_ref(type)  (type->refcount++)

/**
 * Free the datatype, only call this if the datatype is not any more in use!
 */
void smd_type_destroy(smd_dtype_t *type);

/**
 * @Return the number of bytes written to out_buff
 */
size_t smd_type_print(char *out_buff, smd_dtype_t *type);

void smd_type_ser(smd_string_stream_t* s, smd_dtype_t *type);

smd_dtype_t *smd_type_from_ser(char *str);

void smd_type_iterate(smd_dtype_t *type, char *buff, void (*iter)(smd_dtype_t *t, void *buff));


#ifdef __cplusplus
}
#endif

#endif
