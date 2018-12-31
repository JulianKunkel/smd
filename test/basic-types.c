#include <assert.h>
#include <stdio.h>
#include <stdint.h>

#include <smd.h>

static void iter(int id, const char*name){
  printf("%d: %s\n", id, name);
}


int main(){
  int id;
  int id2;
  int ret;
  smd_attr_t * attr = smd_attr_new("root", SMD_TYPE_STRING, "this is a test", & id);

  for(int i= 0; i < 100; i++){
    int a = i;
    char buff[100];
    sprintf(buff, "child%d", i);
    smd_attr_t * attr2 = smd_attr_new(buff, SMD_TYPE_INT32, & a, & id2);
    ret = smd_attr_link(attr, attr2, 0);
    assert(ret == SMD_ATTR_LINKED);

    int32_t b = -1;
    smd_attr_copy_value(attr2, (void**) & b);
    assert(b == i);
  }

  smd_iterate(attr, iter);
  smd_attr_destroy(attr);

  return 0;
}
