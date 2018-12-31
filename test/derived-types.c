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
  smd_attr_t * attr = smd_attr_new("root", SMD_DTYPE_STRING, "this is a test", & id);

  smd_iterate(attr, iter);
  smd_attr_destroy(attr);

  printf("OK\n");

  return 0;
}
