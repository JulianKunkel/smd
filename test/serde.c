#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#include <smd.h>

static int count;

static void iter(int id, const char*name){
  printf("%d: %s\n", id, name);
  count++;
}

int main(){
  int id;
  int id2;
  int ret;

  smd_dtype_t * t_arr = smd_type_array(SMD_DTYPE_STRING, 4);

  printf("size: %zu extent: %zu\n", smd_type_get_size(t_arr), smd_type_get_extent(t_arr));

  struct test{
    int16_t val;
    char * names[4];
    int32_t val2[3];
  };

  struct test v = {4711,
    {"hans", "fritz", "rudolf", "mayer"},
    {11,48812,22}
  };

  size_t offsets[3] = {
      offsetof(struct test, val),
      offsetof(struct test, names),
      offsetof(struct test, val2)
  };
  char * names[3] = {"testvalvaltest", "nameemam\n", "v12321v"};
  smd_dtype_t * t_ext = smd_type_extent(4, 12, SMD_DTYPE_INT32);

  smd_dtype_t * types[3] = {SMD_DTYPE_INT16, t_arr, t_ext};
  smd_dtype_t * t_struct = smd_type_struct(3, offsets, sizeof(struct test), names, types);

  char buff[1024];
  size_t count;
  count = smd_type_ser(buff, t_struct);
  printf("%zu: %s\n", count, buff);
  smd_dtype_t * t_deser = smd_type_from_ser(buff);
  count = smd_type_print(buff, t_deser);
  printf("SerDe: %zu: %s\n", count, buff);

  char buff2[1024];
  size_t count2;
  count2 = smd_type_print(buff2, t_struct);
  printf("%zu: %s\n", count2, buff2);
  assert(count == count2);
  assert(strcmp(buff, buff2) == 0);

  smd_type_unref(& t_struct);
  smd_type_unref(& t_arr);
  smd_type_unref(& t_deser);


  printf("OK\n");

  return 0;
}
