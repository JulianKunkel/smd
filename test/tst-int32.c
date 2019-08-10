#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {
  int id = 0;
  int ret;

  char *name = "this is a test";
  smd_attr_t *attr = smd_attr_new("root", SMD_DTYPE_STRING, name, id);
  char *ptr = (char *)16;
  smd_attr_copy_value(attr, &ptr);
  assert(strcmp(ptr, "this is a test") == 0);

  char buff[100];
  strcpy(buff, "child");

  // **************************************************************************************
  // SMD_DTYPE_INT32
  {
    printf("\n\nTesting INT32!\n");

    int32_t i32 = -20000000;

    int32_t i32_ = 0;
    int64_t i64_ = 0;

    {
      printf("\n\nint64_t!\n");

      smd_attr_t *attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_INT64, SMD_DTYPE_INT32, &i32, id);
      if (attr1 == NULL) {
        printf("\nSorry... It's not possible to make this conversion! :(\n");
      } else {
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(int64_t, int32) = %d", i32);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT64, (void **)&i64_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT32, (void **)&i32_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT64, int64_t) = %ld", i64_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT32, int32) = %d\n\n", i32_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }
  }
  return 0;
}
