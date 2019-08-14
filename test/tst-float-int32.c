#include <assert.h>
#include <float.h>
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
  // SMD_DTYPE_FLOAT
  {
    printf("\n\nTesting FLOAT!\n");

    // float f = INT32_MAX;
    // float f = 2147483648;
    float f = 2147483600;
    // float f = 2147480000;

    int32_t i32_ = 0;
    uint32_t ui32_ = 0;
    float f_ = 0;

    printf("\nProblem detected in smd-core.c:421\n");

    printf("\nsmd-core.c:421\t\tif (ov <= INT32_MIN || ov > INT32_MAX)\n");
    printf("\nsmd-core.c:421\t\tif (ov <= INT32_MIN || ov >= INT32_MAX)\n");

    {
      printf("\n\nint32_t!\n");

      smd_attr_t *attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_INT32, SMD_DTYPE_FLOAT, &f, id);
      if (attr1 == NULL) {
        printf("\nSorry... It's not possible to make this conversion! :(\n");
      } else {
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(int32_t, float) = %f", (double)f);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT32, (void **)&i32_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_FLOAT, (void **)&f_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_UINT32, int32_t) = %d", i32_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_FLOAT, float) = %f", (double)f_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      printf("\n\nuint32_t!\n");

      smd_attr_t *attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_UINT32, SMD_DTYPE_FLOAT, &f, id);
      if (attr1 == NULL) {
        printf("\nSorry... It's not possible to make this conversion! :(\n");
      } else {
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(uint32_t, float) = %f", (double)f);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_UINT32, (void **)&ui32_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_FLOAT, (void **)&f_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_UINT32, uint32_t) = %d", ui32_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_FLOAT, float) = %f", (double)f_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

  }

  printf("\n\n");

  // **************************************************************************************

  return 0;
}
