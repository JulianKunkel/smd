#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

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

  smd_dtype_t * t_arr = smd_type_array(SMD_DTYPE_STRING, 10);

  printf("size: %zu extent: %zu\n", smd_type_get_size(t_arr), smd_type_get_extent(t_arr));

  size_t offsets[3] = {0, 10, 100};
  char * names[3] = {"int", "names", NULL};
  smd_dtype_t * types[3] = { SMD_DTYPE_INT16, t_arr, SMD_DTYPE_UB};
  smd_dtype_t * t_struct = smd_type_struct(3, offsets, names, types);

  printf("size: %zu extent: %zu\n", smd_type_get_size(t_struct), smd_type_get_extent(t_struct));

  smd_attr_t * attr = smd_attr_new("root", SMD_DTYPE_STRING, "this is a test", & id);
  smd_iterate(attr, iter);
  smd_attr_destroy(attr);

  smd_type_unref(& t_struct);
  smd_type_unref(& t_arr);


  printf("OK\n");

  return 0;
}
