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


struct smd_attr_t{
  const char 	* name;
  smd_dtype_t * type;
	void 				* value; // if value != NULL, we are the owner of the data
	int id;

	int children; // number of child attributes
	int childSlots;
	smd_attr_t * parent;
  smd_attr_t ** childs;
};

/**
 * Constructors
 */



/**
 */
smd_attr_t * smd_attr_new(const char * name, smd_dtype_t *type, const void * val, int * out_id);


/**
 */
void smd_attr_destroy(smd_attr_t * attr);

/**
 */
void smd_iterate(smd_attr_t * attr, void (*iter)(int id, const char*name));

typedef enum{
	SMD_ATTR_LINKED,
	SMD_ATTR_REPLACED,
	SMD_ATTR_EEXIST
} smd_link_ret_t;

/**
 */
smd_link_ret_t smd_attr_link(smd_attr_t * parent, smd_attr_t * child, int allow_replace);

void smd_attr_unlink_pos(smd_attr_t * parent, int pos);

/**
 * Retrieve a position for an attribute to manipulate the attribute
 */
int smd_find_position_by_id(const smd_attr_t * attr, int id);
int smd_find_position_by_name(const smd_attr_t * attr, const char * name);

smd_attr_t * smd_attr_get_child  (const smd_attr_t * attr, int pos);

/**
 * The function copies the value of the attribute into the pointer of out_val
 * if out_val is of primitive type, then out_val is expected to point to a variable of a primitive.
 * if out_val is a complex type (e.g., string), then provides a pointer to the new value
 */
void smd_attr_copy_value(smd_attr_t * attr, void * out_val);

/**
 * Return a pointer to the data value, do not modify it!
 */
void * smd_attr_get_value(smd_attr_t * attr);

const char * smd_attr_get_name(smd_attr_t * attr);

/**
 */
int    smd_attr_count    (const smd_attr_t * attr);

/**
 */
size_t smd_attr_print(char * buff, smd_attr_t * attr);


#endif
