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
    int32_t val2;
  };

  struct test v = {4711,
    {"hans", "fritz", "rudolf", "mayer"},
    48812
  };

  size_t offsets[3] = {
      offsetof(struct test, val),
      offsetof(struct test, names),
      offsetof(struct test, val2)
  };
  char * names[3] = {"val", "names", "val2"};
  smd_dtype_t * types[3] = { SMD_DTYPE_INT16, t_arr, SMD_DTYPE_INT32};
  smd_dtype_t * t_struct = smd_type_struct(3, offsets, sizeof(struct test), names, types);

  printf("struct size: %zu extent: %zu\n", smd_type_get_size(t_struct), smd_type_get_extent(t_struct));


  smd_attr_t * attr = smd_attr_new("root", t_struct, & v, id);

  struct test h = {4722, {NULL, NULL, NULL, NULL}, 3434};
  smd_attr_copy_value(attr, & h);
  printf("%d %d %s %s %s %s\n", h.val, h.val2,  h.names[0], h.names[1], h.names[2], h.names[3]);
  assert(h.val == v.val);
  assert(h.val2 == v.val2);
  assert(strcmp(h.names[1], v.names[1]) == 0);

  size_t count;
  char buff[2048];
  count = smd_attr_ser_json(buff, attr);
  printf("Attr: %zu: %s\n", count, buff);

  smd_attr_destroy(attr);
  count = smd_type_print(buff, t_struct);
  printf("Type: %zu: %s\n", count, buff);

  smd_type_unref(& t_struct);
  smd_type_unref(& t_arr);


  printf("OK\n");

  return 0;
}
