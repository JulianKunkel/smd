#include <assert.h>
#include <stdint.h>
#include <stdio.h>
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

  for (int i = 0; i < 1; i++) {
    // int a = i;
    char buff[100];
    sprintf(buff, "child%d", i);

    // int8_t i8 = -120;
    // int16_t i16 = -30000;
    // int32_t i32 = -20000000;
    // int64_t i64 = -2^60;
    // uint8_t ui8 = 200;
    // uint16_t ui16 = 50000;
    // uint32_t ui32 = 200000000;
    // uint64_t ui64 = 2^60;
    // float f = 1.0e35;
    // char c = 'c';

    // **************************************************************************************
    // SMD_DTYPE_DOUBLE
{

    printf("\n\nTesting Double!\n");

    double d = 1.7e300;
    // double d = 3.14;

    // SMD_DTYPE_INT8

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
    char c_ = 'a';

    {
      printf("\n\nint8_t!\n");

      smd_attr_t *attr1 = smd_attr_new_memtype(buff, SMD_DTYPE_INT8, SMD_DTYPE_DOUBLE, &d, id);
      ret = smd_attr_link(attr, attr1, 0);
      assert(ret == SMD_ATTR_LINKED);

      printf("\nsmd_attr_new_memtype(int8_t, double) = %lf", d);

      // void *val_a1 = smd_attr_get_value(attr1);
      // int8_t *a1 = (int8_t *)&val_a1;

      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_INT8, (void **)&i8_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }
      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }

      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_INT8, int8_t) = %d", i8_);
      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_DOUBLE, double) = %lf", d_);

      smd_attr_destroy(attr1);
      smd_attr_unlink_pos(attr, 0);

    }

    {
      printf("\n\nint16_t!\n");

      smd_attr_t *attr1 = smd_attr_new_memtype(buff, SMD_DTYPE_INT16, SMD_DTYPE_DOUBLE, &d, id);
      ret = smd_attr_link(attr, attr1, 0);
      assert(ret == SMD_ATTR_LINKED);

      printf("\nsmd_attr_new_memtype(int16_t, double) = %lf", d);

      // void *val_a1 = smd_attr_get_value(attr1);
      // int16_t *a1 = (int16_t *)&val_a1;

      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_INT16, (void **)&i16_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }
      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }

      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_INT16, int16_t) = %d", i16_);
      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_DOUBLE, double) = %lf", d_);

      smd_attr_destroy(attr1);
      smd_attr_unlink_pos(attr, 0);

    }

    {
      printf("\n\nint32_t!\n");

      smd_attr_t *attr1 = smd_attr_new_memtype(buff, SMD_DTYPE_INT32, SMD_DTYPE_DOUBLE, &d, id);
      ret = smd_attr_link(attr, attr1, 0);
      assert(ret == SMD_ATTR_LINKED);

      printf("\nsmd_attr_new_memtype(uint32_t, double) = %lf", d);

      // void *val_a1 = smd_attr_get_value(attr1);
      // uint32_t *a1 = (uint32_t *)&val_a1;

      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_INT32, (void **)&i32_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }
      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }

      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_UINT32, int32_t) = %d", i32_);
      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_DOUBLE, double) = %lf", d_);

      smd_attr_destroy(attr1);
      smd_attr_unlink_pos(attr, 0);

    }

    {
      printf("\n\nint64_t!\n");

      smd_attr_t *attr1 = smd_attr_new_memtype(buff, SMD_DTYPE_INT64, SMD_DTYPE_DOUBLE, &d, id);
      ret = smd_attr_link(attr, attr1, 0);
      assert(ret == SMD_ATTR_LINKED);

      printf("\nsmd_attr_new_memtype(int64_t, double) = %lf", d);

      // void *val_a1 = smd_attr_get_value(attr1);
      // int64_t *a1 = (int64_t *)&val_a1;

      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_INT64, (void **)&i64_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }
      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }

      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_INT64, int64_t) = %ld", i64_);
      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_DOUBLE, double) = %lf", d_);

      smd_attr_destroy(attr1);
      smd_attr_unlink_pos(attr, 0);

    }

    {
      printf("\n\nuint8_t!\n");

      smd_attr_t *attr1 = smd_attr_new_memtype(buff, SMD_DTYPE_UINT8, SMD_DTYPE_DOUBLE, &d, id);
      ret = smd_attr_link(attr, attr1, 0);
      assert(ret == SMD_ATTR_LINKED);

      printf("\nsmd_attr_new_memtype(uint8_t, double) = %lf", d);

      // void *val_a1 = smd_attr_get_value(attr1);
      // uint8_t *a1 = (uint8_t *)&val_a1;

      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_UINT8, (void **)&ui8_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }
      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }

      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_UINT8, uint8_t) = %d", ui8_);
      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_DOUBLE, double) = %lf", d_);

      smd_attr_destroy(attr1);
      smd_attr_unlink_pos(attr, 0);

    }

    {
      printf("\n\nuint16_t!\n");

      smd_attr_t *attr1 = smd_attr_new_memtype(buff, SMD_DTYPE_UINT16, SMD_DTYPE_DOUBLE, &d, id);
      ret = smd_attr_link(attr, attr1, 0);
      assert(ret == SMD_ATTR_LINKED);

      printf("\nsmd_attr_new_memtype(uint16_t, double) = %lf", d);

      // void *val_a1 = smd_attr_get_value(attr1);
      // uint16_t *a1 = (uint16_t *)&val_a1;

      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_UINT16, (void **)&ui16_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }
      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }

      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_UINT16, uint16_t) = %d", ui16_);
      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_DOUBLE, double) = %lf", d_);

      smd_attr_destroy(attr1);
      smd_attr_unlink_pos(attr, 0);

    }

    {
      printf("\n\nuint32_t!\n");

      smd_attr_t *attr1 = smd_attr_new_memtype(buff, SMD_DTYPE_UINT32, SMD_DTYPE_DOUBLE, &d, id);
      ret = smd_attr_link(attr, attr1, 0);
      assert(ret == SMD_ATTR_LINKED);

      printf("\nsmd_attr_new_memtype(uint32_t, double) = %lf", d);

      // void *val_a1 = smd_attr_get_value(attr1);
      // uint32_t *a1 = (uint32_t *)&val_a1;

      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_UINT32, (void **)&ui32_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }
      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }

      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_UINT32, uint32_t) = %d", ui32_);
      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_DOUBLE, double) = %lf", d_);

      smd_attr_destroy(attr1);
      smd_attr_unlink_pos(attr, 0);

    }

    {
      printf("\n\nuint64_t!\n");

      smd_attr_t *attr1 = smd_attr_new_memtype(buff, SMD_DTYPE_UINT64, SMD_DTYPE_DOUBLE, &d, id);
      ret = smd_attr_link(attr, attr1, 0);
      assert(ret == SMD_ATTR_LINKED);

      printf("\nsmd_attr_new_memtype(uint64_t, double) = %lf", d);

      // void *val_a1 = smd_attr_get_value(attr1);
      // uint64_t *a1 = (uint64_t *)&val_a1;

      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_UINT64, (void **)&ui64_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }
      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }

      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_UINT64, uint64_t) = %ld", ui64_);
      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_DOUBLE, double) = %lf", d_);

      smd_attr_destroy(attr1);
      smd_attr_unlink_pos(attr, 0);

    }

    {
      printf("\n\nfloat!\n");

      smd_attr_t *attr1 = smd_attr_new_memtype(buff, SMD_DTYPE_FLOAT, SMD_DTYPE_DOUBLE, &d, id);
      ret = smd_attr_link(attr, attr1, 0);
      assert(ret == SMD_ATTR_LINKED);

      printf("\nsmd_attr_new_memtype(float, double) = %lf", d);

      // void *val_a1 = smd_attr_get_value(attr1);
      // float *a1 = (float *)&val_a1;

      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_FLOAT, (void **)&f_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }
      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }
      float x = f_;

      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_FLOAT, float) = %d.%.6d", (int)x, (int)((x-(int)x)*1000000));
      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_FLOAT, float) = %f", f_);
      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_DOUBLE, double) = %lf", d_);

      smd_attr_destroy(attr1);
      smd_attr_unlink_pos(attr, 0);

    }

    {

      printf("\n\ndouble!\n");

      smd_attr_t *attr1 = smd_attr_new_memtype(buff, SMD_DTYPE_DOUBLE, SMD_DTYPE_DOUBLE, &d, id);
      ret = smd_attr_link(attr, attr1, 0);
      assert(ret == SMD_ATTR_LINKED);

      printf("\nsmd_attr_new_memtype(double, double) = %lf", d);

      // void *val_a1 = smd_attr_get_value(attr1);
      // double *a1 = (double *)&val_a1;

      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }
      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }

      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_DOUBLE, double) = %lf", d_);
      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_DOUBLE, double) = %lf", d_);

      smd_attr_destroy(attr1);
      smd_attr_unlink_pos(attr, 0);

    }

    {

      printf("\n\nchar!\n");

      smd_attr_t *attr1 = smd_attr_new_memtype(buff, SMD_DTYPE_CHAR, SMD_DTYPE_DOUBLE, &d, id);
      ret = smd_attr_link(attr, attr1, 0);
      assert(ret == SMD_ATTR_LINKED);

      printf("\nsmd_attr_new_memtype(double, double) = %lf", d);

      // void *val_a1 = smd_attr_get_value(attr1);
      // char *a1 = (char *)&val_a1;

      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_CHAR, (void **)&c_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }
      ret = smd_attr_copy_value_memtype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
      if (ret) {
        printf("\nSorry... :(\n");
        return(0);
      }

      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_CHAR, char) = %d", c_);
      printf("\nsmd_attr_copy_value_memtype(SMD_DTYPE_DOUBLE, double) = %lf", d_);

      smd_attr_destroy(attr1);
      smd_attr_unlink_pos(attr, 0);

    }

    printf("\n\nDouble OK!\n\n");

}

}

  // **************************************************************************************


  return 0;
}
