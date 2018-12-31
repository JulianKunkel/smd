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
  char * ptr = 0;
  smd_attr_copy_value(attr, (void*) & ptr);
  assert(strcmp(ptr, "this is a test") == 0);

  for(int i= 0; i < 100; i++){
    int a = i;
    char buff[100];
    sprintf(buff, "child%d", i);
    smd_attr_t * attr2 = smd_attr_new(buff, SMD_DTYPE_INT32, & a, & id2);
    ret = smd_attr_link(attr, attr2, 0);
    assert(ret == SMD_ATTR_LINKED);

    int32_t b = -1;
    void * val_p = smd_attr_get_value(attr2);
    int32_t * t_p = (int32_t*) & val_p;
    assert(*t_p == i);

    smd_attr_copy_value(attr2, (void**) & b);
    assert(b == i);
  }

  for(int i=0; i < 100; i++){
    smd_attr_t * attr3 = smd_attr_get_child(attr, i);
    const char * n = smd_attr_get_name(attr3);
    int32_t b = -1;
    smd_attr_copy_value(attr3, (void*) & b);
    assert(b == i);
    char buff[100];
    sprintf(buff, "child%d", i);
    assert(strcmp(buff, n) == 0);
  }

  for(int i=50; i > 0; i--){
    int pos = i*2 - 1;
    smd_attr_unlink_pos(attr, pos);
  }

  count = 0;
  smd_iterate(attr, iter);
  assert( count == 51 );
  smd_attr_destroy(attr);

  printf("OK\n");

  return 0;
}
