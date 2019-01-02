#ifndef HSMD_INTERNAL_HEADER_H_
#define HSMD_INTERNAL_HEADER_H_

#include <smd.h>
#include <assert.h>
#include <string.h>


/*
 * Duplicate the string, removing all invalid characters
 */
char * smd_dup_escaped_varname(const char * name);
size_t smd_type_ser_i(char * buff, smd_dtype_t * t);
smd_dtype_t * smd_type_from_ser_i(char ** str);

#endif
