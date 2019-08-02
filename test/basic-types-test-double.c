#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <smd.h>

int main() {
  int id = 0;
  int id2 = 1;
  int ret;

  char *name = "this is a test";
  smd_attr_t *attr = smd_attr_new("root", SMD_DTYPE_STRING, name, id);
  char *ptr = (char *)16;
  smd_attr_copy_value(attr, &ptr);
  assert(strcmp(ptr, "this is a test") == 0);

  for (int i = 0; i < 1; i++) {
    // int a = i;
    char buff[100];
    sprintf(buff, "child%d", i);

    double d = 3.14;
    smd_attr_t *attr1 = smd_attr_new_memtype(buff, SMD_DTYPE_INT32, SMD_DTYPE_DOUBLE, &d, id2);
    ret = smd_attr_link(attr, attr1, 0);
    assert(ret == SMD_ATTR_LINKED);

    printf("\nsmd_attr_new_memtype(int32_t, double) = %lf\n", d);

    void *val_a1 = smd_attr_get_value(attr1);
    int32_t *a1 = (int32_t *)&val_a1;
    void *val_a2 = smd_attr_get_value(attr1);
    double *a2 = (double *)&val_a2;

    printf("\nsmd_attr_get_value(int32_t) = %d\n", *a1);
    printf("\nsmd_attr_get_value(double) = %lf\n", *a2);

    int32_t b1 = -1;
    smd_attr_copy_value(attr1, (void **)&b1);
    double b2 = -1.1;
    smd_attr_copy_value(attr1, (void **)&b2);

    printf("\nsmd_attr_copy_value_memtype(int32_t) = %d\n", b1);
    printf("\nsmd_attr_copy_value_memtype(double) = %lf\n", b2);

    int32_t c1 = -1;
    int32_t c2 = -1;
    double c3 = -1.1;
    double c4 = -1.1;
    ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_INT32, (void **)&c1);
    ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_DOUBLE, (void **)&c2);
    ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_INT32, (void **)&c3);
    ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_DOUBLE, (void **)&c4);
    printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_INT32, int32_t) = %d\n", c1);
    printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_DOUBLE, int32_t) = %d\n", c2);
    printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_INT32, double) = %lf\n", c3);
    printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_DOUBLE, double) = %lf\n", c4);

    // smd_attr_t *attr2 = smd_attr_new(buff, SMD_DTYPE_INT32, &a, id2);
    // ret = smd_attr_link(attr1, attr2, 0);
    // assert(ret == SMD_ATTR_LINKED);
    //
    // void *val_p2 = smd_attr_get_value(attr2);
    // int32_t *t_p2 = (int32_t *)&val_p2;
    // assert(*t_p2 == i);
    //
    // int32_t b = -1;
    // smd_attr_copy_value(attr2, (void **)&b);
    // assert(b == i);
    //
    // printf("\na = %d, t_p = %d, b = %d, i = %d\n\n", a, *t_p2, b, i);
  }

  printf("\n\nOK\n\n");

  return 0;
}
