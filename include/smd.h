#ifndef HSMD_HEADER_H_
#define HSMD_HEADER_H_

#include <smd-datatype.h>

/**
 * The SMD library is intented for two purposes:
 * 1) An annotation mechanism allowing to annotate any existing primitive and complex data structures with attributes; allowing to traverse and access the original data.
 * 2) By extending on (1) the management of data and attributes together.
 * A purpose for (1) is to support introspection over variables.
 * Only (2) is implemented.

 * Organisation of attributes:
 * Attributes are key/value pairs.
 * An attribute is also identified by an unique ID.
 * Attributes are organized hierarchically, i.e., attributes to attributes are possible.
 * The key is always a unique string as part of an attribute, the value can be of any supported datatype.
 */

typedef struct smd_attr_t smd_attr_t;

struct smd_attr_t {
  const char *name;
  smd_dtype_t *type;
  void *value; // if value != NULL, we are the owner of the data
  int id;

  unsigned int children; // number of child attributes
  unsigned int childSlots;
  smd_attr_t *parent;
  smd_attr_t **childs;
};

/**
 * Constructors
 */

/**
 */
smd_attr_t *smd_attr_new(const char *name, smd_dtype_t *type, const void *val, int id);

/*
 Return NULL if data cannot be converted lossless
 */
smd_attr_t *smd_attr_new_memtype(const char *name, smd_dtype_t *type, smd_dtype_t *memtype, const void *val, int id);

/**
 */
void smd_attr_destroy(smd_attr_t *attr);

/**
 */
void smd_iterate(smd_attr_t *attr, void (*iter)(int id, const char *name));

typedef enum {
  SMD_ATTR_LINKED,
  SMD_ATTR_REPLACED,
  SMD_ATTR_EEXIST
} smd_link_ret_t;

/**
 */
smd_link_ret_t smd_attr_link(smd_attr_t *parent, smd_attr_t *child, int allow_replace);

void smd_attr_unlink_pos(smd_attr_t *parent, unsigned int pos);

/**
 * Retrieve a position for an attribute to manipulate the attribute
 */
int smd_find_position_by_id(const smd_attr_t *attr, int id);
int smd_find_position_by_name(const smd_attr_t *attr, const char *name);

smd_attr_t *smd_attr_get_child(const smd_attr_t *attr, unsigned int pos);
smd_attr_t *smd_attr_get_child_by_name(const smd_attr_t *attr, const char *name);

/**
 * The function copies the value of the attribute into the pointer of out_val
 * if out_val is of primitive type, then out_val is expected to point to a variable of a primitive.
 * if out_val is a complex type (e.g., string), then provides a pointer to the new value
 * TODO clarify semantics, maybe provide a function that copies from one type of attribute to another format of attribute?
 */
void smd_attr_copy_value(smd_attr_t *attr, void *out_val);

/*
 Converts the data, return 1 if overflow
 */
int smd_attr_copy_value_memtype(smd_attr_t *attr, smd_dtype_t *mem_type, void *out_val);

/**
 * @param[in] attr xx
 * @Return Pointer to the data value, do not modify or free it.
 * This is
 */
void *smd_attr_get_value(smd_attr_t *attr);
smd_basic_type_t smd_attr_get_type(smd_attr_t *attr);

const char *smd_attr_get_name(smd_attr_t *attr);

/*
 * Return the number of elements
 */
uint64_t smd_attr_elems(smd_attr_t const *attr);

/**
 */
int smd_attr_count(const smd_attr_t *attr);

/*
 Serialize to the stream the value according to the datatype
 */
void smd_ser_json_value(smd_string_stream_t*s, void *val, smd_dtype_t *t);
void smd_copy_value(smd_dtype_t *type, void * to, void * from);

/**
 */
void smd_attr_ser_json(smd_string_stream_t*s, smd_attr_t *attr);

size_t smd_attr_create_from_json(char *json, size_t size, smd_attr_t **out_attr);

//smd_string_stream_t is supposed to work as a wrapper that isolates the rest of the code from the question, whether `open_memstream()` is usable.
//If it were not usable, we can swap out the implementation of smd_string_stream_t, but keep its interface.
smd_string_stream_t* smd_string_stream_create();
void smd_string_stream_printf(smd_string_stream_t* stream, const char* format, ...)
  __attribute__((format(printf, 2, 3)));  //allow the compiler to check the argument types
char* smd_string_stream_close(smd_string_stream_t* stream, size_t* out_size); //destructs the stream and returns the contained data as a suitably allocated string

#endif
