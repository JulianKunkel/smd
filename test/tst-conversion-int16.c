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
  // SMD_DTYPE_INT16
  {
    printf("\n\nTesting INT16!\n");

    // int16_t i16 = 120;
    // int16_t i16 = 240;
    // int16_t i16 = 30000;
    // int16_t i16 = -120;
    // int16_t i16 = -240;
    int16_t i16 = -30000;

    int i = 0, conv[11];

    int8_t i8_ = 0;
    int16_t i16_ = 0;
    int32_t i32_ = 0;
    int64_t i64_ = 0;
    uint8_t ui8_ = 0;
    uint16_t ui16_ = 0;
    uint32_t ui32_ = 0;
    uint64_t ui64_ = 0;
    float f_ = 0;
    double d_ = 0;
    char c_ = ' ';

    {
      printf("\n\nint8_t!\n");
      smd_attr_t *attr1;

      attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_INT8, SMD_DTYPE_INT16, &i16, id);
      if (attr1 == NULL) {
        conv[i++] = 0;
        printf("\nSorry... It's not possible to make this conversion! :(\n");
        // return(0);
      } else {
        conv[i++] = 1;

        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(int8_t, int16) = %d", i16);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT8, (void **)&i8_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT16, (void **)&i16_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT8, int8_t) = %d", i8_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT16, int16) = %d", i16_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      printf("\n\nint16_t!\n");

      smd_attr_t *attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_INT16, SMD_DTYPE_INT16, &i16, id);
      if (attr1 == NULL) {
        conv[i++] = 0;
        printf("\nSorry... It's not possible to make this conversion! :(\n");
      } else {
        conv[i++] = 1;
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(int16_t, int16) = %d", i16);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT16, (void **)&i16_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT16, (void **)&i16_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT16, int16_t) = %d", i16_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT16, int16) = %d", i16_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      printf("\n\nint32_t!\n");

      smd_attr_t *attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_INT32, SMD_DTYPE_INT16, &i16, id);
      if (attr1 == NULL) {
        conv[i++] = 0;
        printf("\nSorry... It's not possible to make this conversion! :(\n");
      } else {
        conv[i++] = 1;
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(uint32_t, int16) = %d", i16);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT32, (void **)&i32_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT16, (void **)&i16_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_UINT32, int32_t) = %d", i32_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT16, int16) = %d", i16_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      printf("\n\nint64_t!\n");

      smd_attr_t *attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_INT64, SMD_DTYPE_INT16, &i16, id);
      if (attr1 == NULL) {
        conv[i++] = 0;
        printf("\nSorry... It's not possible to make this conversion! :(\n");
      } else {
        conv[i++] = 1;
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(int64_t, int16) = %d", i16);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT64, (void **)&i64_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT16, (void **)&i16_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT64, int64_t) = %ld", i64_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT16, int16) = %d", i16_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      printf("\n\nuint8_t!\n");

      smd_attr_t *attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_UINT8, SMD_DTYPE_INT16, &i16, id);
      if (attr1 == NULL) {
        conv[i++] = 0;
        printf("\nSorry... It's not possible to make this conversion! :(\n");
      } else {
        conv[i++] = 1;
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(uint8_t, int16) = %d", i16);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_UINT8, (void **)&ui8_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT16, (void **)&i16_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_UINT8, uint8_t) = %d", ui8_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT16, int16) = %d", i16_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      printf("\n\nuint16_t!\n");

      smd_attr_t *attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_UINT16, SMD_DTYPE_INT16, &i16, id);
      if (attr1 == NULL) {
        conv[i++] = 0;
        printf("\nSorry... It's not possible to make this conversion! :(\n");
      } else {
        conv[i++] = 1;
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(uint16_t, int16) = %d", i16);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_UINT16, (void **)&ui16_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT16, (void **)&i16_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_UINT16, uint16_t) = %d", ui16_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT16, int16) = %d", i16_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      printf("\n\nuint32_t!\n");

      smd_attr_t *attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_UINT32, SMD_DTYPE_INT16, &i16, id);
      if (attr1 == NULL) {
        conv[i++] = 0;
        printf("\nSorry... It's not possible to make this conversion! :(\n");
      } else {
        conv[i++] = 1;
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(uint32_t, int16) = %d", i16);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_UINT32, (void **)&ui32_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT16, (void **)&i16_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_UINT32, uint32_t) = %d", ui32_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT16, int16) = %d", i16_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      printf("\n\nuint64_t!\n");

      smd_attr_t *attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_UINT64, SMD_DTYPE_INT16, &i16, id);
      if (attr1 == NULL) {
        conv[i++] = 0;
        printf("\nSorry... It's not possible to make this conversion! :(\n");
      } else {
        conv[i++] = 1;
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(uint64_t, int16) = %d", i16);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_UINT64, (void **)&ui64_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT16, (void **)&i16_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_UINT64, uint64_t) = %lu", ui64_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT16, int16) = %d", i16_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      printf("\n\nfloat!\n");

      smd_attr_t *attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_FLOAT, SMD_DTYPE_INT16, &i16, id);
      if (attr1 == NULL) {
        conv[i++] = 0;
        printf("\nSorry... It's not possible to make this conversion! :(\n");
      } else {
        conv[i++] = 1;
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(float, int16) = %d", i16);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_FLOAT, (void **)&f_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT16, (void **)&i16_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_FLOAT, float) = %f", (double)f_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT16, int16) = %d", i16_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      printf("\n\ndouble!\n");

      smd_attr_t *attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_DOUBLE, SMD_DTYPE_INT16, &i16, id);
      if (attr1 == NULL) {
        conv[i++] = 0;
        printf("\nSorry... It's not possible to make this conversion! :(\n");
      } else {
        conv[i++] = 1;
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(int16, int16) = %d", i16);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT16, (void **)&i16_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_DOUBLE, double) = %lf", d_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT16, int16) = %d", i16_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      printf("\n\nchar!\n");

      smd_attr_t *attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_CHAR, SMD_DTYPE_INT16, &i16, id);
      if (attr1 == NULL) {
        conv[i++] = 0;
        printf("\nSorry... It's not possible to make this conversion! :(\n");
      } else {
        conv[i++] = 1;
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(int16, int16) = %d", i16);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_CHAR, (void **)&c_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT16, (void **)&i16_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_CHAR, char) = %c", c_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT16, int16) = %d", i16_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    printf("\n\nSummary of INT16 Conversions\n");

    i = 0;

    if (conv[i++] == 0)
      printf("\nThe conversion from int16 to int8_t was not possible!");
    else
      printf("\nThe conversion from int16 to int8_t was successull!");

    if (conv[i++] == 0)
      printf("\nThe conversion from int16 to int16_t was not possible!");
    else
      printf("\nThe conversion from int16 to int16_t was successull!");

    if (conv[i++] == 0)
      printf("\nThe conversion from int16 to int32_t was not possible!");
    else
      printf("\nThe conversion from int16 to int32_t was successull!");

    if (conv[i++] == 0)
      printf("\nThe conversion from int16 to int64_t was not possible!");
    else
      printf("\nThe conversion from int16 to int64_t was successull!");

    if (conv[i++] == 0)
      printf("\nThe conversion from int16 to uint8_t was not possible!");
    else
      printf("\nThe conversion from int16 to uint8_t was successull!");

    if (conv[i++] == 0)
      printf("\nThe conversion from int16 to uint16_t was not possible!");
    else
      printf("\nThe conversion from int16 to uint16_t was successull!");

    if (conv[i++] == 0)
      printf("\nThe conversion from int16 to uint32_t was not possible!");
    else
      printf("\nThe conversion from int16 to uint32_t was successull!");

    if (conv[i++] == 0)
      printf("\nThe conversion from int16 to uint64_t was not possible!");
    else
      printf("\nThe conversion from int16 to uint64_t was successull!");

    if (conv[i++] == 0)
      printf("\nThe conversion from int16 to float was not possible!");
    else
      printf("\nThe conversion from int16 to float was successull!");

    if (conv[i++] == 0)
      printf("\nThe conversion from int16 to double was not possible!");
    else
      printf("\nThe conversion from int16 to double was successull!");

    if (conv[i++] == 0)
      printf("\nThe conversion from int16 to char was not possible!\n\n");
    else
      printf("\nThe conversion from int16 to char was successull!\n\n");
  }

  // **************************************************************************************

  return 0;
}
