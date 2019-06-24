#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#include <smd.h>

static int count;

int main(){

  smd_dtype_t * t_arr = smd_type_array(SMD_DTYPE_STRING, 4);
  smd_attr_t * attr = smd_attr_new("root", SMD_DTYPE_DTYPE, t_arr, 0);

  size_t count;
  char buff[2048];
  count = smd_attr_ser_json(buff, attr);
  printf("Attr: %zu: %s\n", count, buff);

  smd_attr_t * attr_deser = smd_attr_create_from_json(buff, count);
  smd_dtype_t * orig_dtype = (smd_dtype_t *) smd_attr_get_value(attr_deser);
  smd_type_print(buff, orig_dtype);
  printf("Retrieved datatype %s\n", buff);

  smd_attr_destroy(attr);
  smd_type_unref(& t_arr);


  printf("OK\n");

  return 0;
}
