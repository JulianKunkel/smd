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
  int ret;

  smd_dtype_t * t_arr = smd_type_array(SMD_DTYPE_STRING, 4);

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

  smd_attr_t * attr = smd_attr_new("root", t_struct, & v, & id);
  char * name = "this is a test";
  smd_attr_t * attr2 = smd_attr_new("child", SMD_DTYPE_STRING, name, & id);
  ret = smd_attr_link(attr, attr2, 0);

  smd_attr_t * attr4 = smd_attr_new("unknown", SMD_DTYPE_EMPTY, NULL, & id);
  ret = smd_attr_link(attr, attr4, 0);


  smd_dtype_t * t_ext = smd_type_extent(4, 12, SMD_DTYPE_INT32);

  int32_t val[3] = {11,22,33};
  smd_attr_t * attr3 = smd_attr_new("subchild", t_ext, val, & id);
  ret = smd_attr_link(attr2, attr3, 0);

  count = 0;
  smd_iterate(attr, iter);

  char buff[1024];
  size_t size;
  //size = smd_attr_ser_json(buff, attr2);
  size = smd_attr_ser_json(buff, attr);
  printf("ATTR SER: %zu: %s\n", size, buff);


  char buff2[1024];
  smd_attr_t * attr_deser = smd_attr_create_from_json(buff);
  assert(attr_deser != NULL);
  size_t size2;
  size2 = smd_attr_ser_json(buff2, attr_deser);
  printf("ATTR SER: %zu: %s\n", size2, buff2);
  assert(size == size2);
  assert(strcmp(buff, buff2) == 0);

  smd_attr_destroy(attr);
  smd_type_unref(& t_struct);
  smd_type_unref(& t_arr);

  printf("OK\n");

  return 0;
}
