#ifndef HSMD_INTERNAL_HEADER_H_
#define HSMD_INTERNAL_HEADER_H_

#include <smd.h>
#include <assert.h>
#include <string.h>


/*
 * Duplicate the string, removing all invalid characters
 */
char * smd_dup_escaped_varname(const char * name);

#endif
