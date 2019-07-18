#ifndef HSMD_INTERNAL_HEADER_H_
#define HSMD_INTERNAL_HEADER_H_

#include <assert.h>
#include <smd.h>
#include <string.h>

/*
 * Duplicate the string, removing all invalid characters
 */
char *smd_dup_escaped_varname(const char *name);
smd_dtype_t *smd_type_from_ser_i(char **str);

//smd_string_stream_t is supposed to work as a wrapper that isolates the rest of the code from the question, whether `open_memstream()` is usable.
//If it were not usable, we can swap out the implementation of smd_string_stream_t, but keep its interface.
struct smd_string_stream_t {
  char* string;
  size_t bufferSize, characterCount;
  FILE* stream;
};


#endif
