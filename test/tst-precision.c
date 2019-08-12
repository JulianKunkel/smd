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

  // printf("\nCOPY TO INTERNAL!\n");

  printf("\n****************************************************************");
  printf("\nTesting stardard cases with value equals to 120!");
  printf("\n****************************************************************");

  {
    int32_t ti32 = 120;
    int32_t tui32 = 120;
    int64_t ti64 = 120;
    int64_t tui64 = 120;
    float tf = 120;
    double td = 120;

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
      // case (SMD_TYPE_FLOAT): {
      // float *p = (float *)out;
      //     case (SMD_TYPE_INT32): {
      //       int32_t ov = *(int32_t*)val;
      //       *p = (float) ov;
      //       // check if accuracy is precise enough
      //       if(ov != (int32_t)*p){
      //         return 1;
      //       }
      //       return 0;
      //     }

      printf("\n\nOriginal Type: FLOAT!");
      printf("\nStorage Type: INT32!\n");

      printf("\nFrom GDB!");
      printf("\nOriginal number = %d", ti32);
      // printf("\nStored number = 1593429209");
      // printf("\nRetrieved number = 1593429248");

      smd_attr_t *attr1;

      attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_FLOAT, SMD_DTYPE_INT32, &ti32, id);
      if (attr1 == NULL) {
        printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
      } else {
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(float, int32_t) = %d", ti32);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT32, (void **)&i32_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_FLOAT, (void **)&f_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT32, int32_t) = %d", i32_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_FLOAT, float) = %f", (double)f_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      // case (SMD_TYPE_FLOAT): {
      // float *p = (float *)out;
      //     case (SMD_TYPE_INT64): {
      //       int64_t ov = *(int64_t*)val;
      //       *p = (float) ov;
      //       // check if accuracy is precise enough
      //       if(ov != (int64_t)*p){
      //         return 1;
      //       }

      printf("\n\nOriginal Type: FLOAT!");
      printf("\nStorage Type: INT64!\n");

      printf("\nFrom GDB!");
      printf("\nOriginal number = %ld", ti64);
      // printf("\nStored number = 1593429209");
      // printf("\nRetrieved number = 1593429248");

      smd_attr_t *attr1;

      attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_FLOAT, SMD_DTYPE_INT64, &ti64, id);
      if (attr1 == NULL) {
        printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
      } else {
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(float, int64_t) = %ld", ti64);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT64, (void **)&i64_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_FLOAT, (void **)&f_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT64, int64_t) = %ld", i64_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_FLOAT, float) = %f", (double)f_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      // case (SMD_TYPE_FLOAT): {
      // float *p = (float *)out;
      //       case (SMD_TYPE_UINT32): {
      //         uint32_t ov = *(uint32_t*)val;
      //         *p = (float) ov;
      //         // check if accuracy is precise enough
      //         if(ov != (uint32_t)*p){
      //           return 1;
      //         }
      //         return 0;
      //       }

      printf("\n\nOriginal Type: FLOAT!");
      printf("\nStorage Type: UINT32!\n");

      printf("\nFrom GDB!");
      printf("\nOriginal number = %d", tui32);
      // printf("\nStored number = 1593429209");
      // printf("\nRetrieved number = 1593429248");

      smd_attr_t *attr1;

      attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_FLOAT, SMD_DTYPE_UINT32, &tui32, id);
      if (attr1 == NULL) {
        printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
      } else {
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(float, uint32_t) = %d", tui32);

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

    {
      // case (SMD_TYPE_FLOAT): {
      // float *p = (float *)out;
      //       case (SMD_TYPE_UINT64): {
      //         uint64_t ov = *(uint64_t*)val;
      //         *p = (float) ov;
      //         // check if accuracy is precise enough
      //         if(ov != (uint64_t)*p){
      //           return 1;
      //         }
      //         return 0;
      //       }

      printf("\n\nOriginal Type: FLOAT!");
      printf("\nStorage Type: UINT64!\n");

      printf("\nFrom GDB!");
      printf("\nOriginal number = %lu", tui64);
      // printf("\nStored number = 1593429209");
      // printf("\nRetrieved number = 1593429248");

      smd_attr_t *attr1;

      attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_FLOAT, SMD_DTYPE_UINT64, &tui64, id);
      if (attr1 == NULL) {
        printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
      } else {
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(float, uint64_t) = %lu", tui64);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_UINT64, (void **)&ui64_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_FLOAT, (void **)&f_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_UINT64, uint64_t) = %lu", ui64_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_FLOAT, float) = %f", (double)f_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      // case (SMD_TYPE_DOUBLE): {
      // double *p = (double *)out;
      //     case (SMD_TYPE_INT64): {
      //       int64_t ov = *(int64_t*)val;
      //       *p = (double) ov;
      //       // check if accuracy is precise enough
      //       if(ov != (int64_t)*p){
      //         return 1;
      //       }
      //       return 0;
      //     }

      printf("\n\nOriginal Type: DOUBLE!");
      printf("\nStorage Type: INT64!\n");

      printf("\nFrom GDB!");
      printf("\nOriginal number = %ld", ti64);

      smd_attr_t *attr1;

      attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_DOUBLE, SMD_DTYPE_INT64, &ti64, id);
      if (attr1 == NULL) {
        printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
      } else {
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(double, int64_t) = %ld", ti64);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT64, (void **)&i64_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT64, int64_t) = %ld", i64_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_DOUBLE, double) = %lf", d_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      // case (SMD_TYPE_DOUBLE): {
      // double *p = (double *)out;
      //     case (SMD_TYPE_UINT64): {
      //       uint64_t ov = *(uint64_t*)val;
      //       *p = (double) ov;
      //       // check if accuracy is precise enough
      //       if(ov != (uint64_t)*p){
      //         return 1;
      //       }
      //       return 0;
      //     }

      printf("\n\nOriginal Type: DOUBLE!");
      printf("\nStorage Type: UINT64!\n");

      printf("\nFrom GDB!");
      printf("\nOriginal number = %lu", tui64);

      smd_attr_t *attr1;

      attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_DOUBLE, SMD_DTYPE_UINT64, &tui64, id);
      if (attr1 == NULL) {
        printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
      } else {
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(double, uint64_t) = %lu", tui64);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_UINT64, (void **)&ui64_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_UINT64, uint64_t) = %lu", ui64_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_DOUBLE, double) = %lf", d_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      // case (SMD_TYPE_DOUBLE): {
      // double *p = (double *)out;
      //     case (SMD_TYPE_FLOAT): {
      //       float ov = *(float*)val;
      //       *p = (double) ov;
      //       // check if accuracy is precise enough
      //       if(ov != (float)*p){
      //         return 1;
      //       }
      //       return 0;
      //     }

      printf("\n\nOriginal Type: DOUBLE!");
      printf("\nStorage Type: FLOAT!\n");

      printf("\nFrom GDB!");
      printf("\nOriginal number = %f", (double)tf);
      // printf("\n*(float*)val = ");
      // printf("\n(double)*(float*)val = ");
      // printf("\n*(double*)val = ");

      // printf("\n\nIt stops because of this test: if(ov > 0 && (ov < (double)FLT_MIN || ov > (double)FLT_MAX)");

      // printf("\n\nIt doesn't reach the accuracy check. I'm not even sure this test is necessary in this case.");

      smd_attr_t *attr1;

      attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_DOUBLE, SMD_DTYPE_FLOAT, &tf, id);
      if (attr1 == NULL) {
        printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
      } else {
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(double, float) = %f", (double)tf);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_FLOAT, (void **)&f_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_DOUBLE, double) = %lf", d_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_FLOAT, float) = %f", (double)f_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    printf("\n\n\n****************************************************************");
    printf("\nTesting cases in which the accuracy is not acceptable!");
    printf("\n****************************************************************");

    int32_t i32 = INT32_MIN + 1;
    // int32_t i32 = -2000000000;
    int64_t si32 = 2000000000;
    float fi32 = 2000000000;
    double di32 = 2000000000;

    int64_t i64 = INT64_MIN + 1;
    // int64_t i64 = -9000000000000000000;
    float fi64 = 9000000000000000000;
    double di64 = 9000000000000000000;

    int32_t ui32 = UINT32_MAX;
    // int32_t ui32 = 4294967294;
    // int32_t ui32 = 2000000000;
    int64_t ui64 = UINT64_MAX;
    // int64_t ui64 = 9000000000000000000;

    // float f = FLT_MAX - 5000;
    // float f = 1.0e35;
    double df = 1.0e35;
    float f = 340282346638528859811704183484516000000.0;
    // float f =    340282346638528859811704183484516925440;
    // double d = DBL_MAX - 1;
    // double d = 1.7e300;
    double d = 340282346638528859811704183484516925430.12345;

    {
      // case (SMD_TYPE_FLOAT): {
      // float *p = (float *)out;
      //     case (SMD_TYPE_INT32): {
      //       int32_t ov = *(int32_t*)val;
      //       *p = (float) ov;
      //       // check if accuracy is precise enough
      //       if(ov != (int32_t)*p){
      //         return 1;
      //       }
      //       return 0;
      //     }

      printf("\n\nOriginal Type: FLOAT!");
      printf("\nStorage Type: INT32!\n");

      printf("\nFrom GDB!");
      printf("\nOriginal number = %d", i32);
      printf("\nStored number = -2147483647");
      printf("\nRetrieved number = -2147483648");

      smd_attr_t *attr1;

      attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_FLOAT, SMD_DTYPE_INT32, &i32, id);
      if (attr1 == NULL) {
        printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
      } else {
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(float, int32_t) = %d", i32);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT32, (void **)&i32_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_FLOAT, (void **)&f_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT32, int32_t) = %d", i32_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_FLOAT, float) = %lf", (double)f_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      // case (SMD_TYPE_FLOAT): {
      // float *p = (float *)out;
      //     case (SMD_TYPE_INT64): {
      //       int64_t ov = *(int64_t*)val;
      //       *p = (float) ov;
      //       // check if accuracy is precise enough
      //       if(ov != (int64_t)*p){
      //         return 1;
      //       }

      printf("\n\nOriginal Type: FLOAT!");
      printf("\nStorage Type: INT64!\n");

      printf("\nFrom GDB!");
      printf("\nOriginal number = %ld", i64);
      printf("\nStored number = -9223372036854775807");
      printf("\nRetrieved number = -9223372036854775808");

      smd_attr_t *attr1;

      attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_FLOAT, SMD_DTYPE_INT64, &i64, id);
      if (attr1 == NULL) {
        printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
      } else {
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(float, int64_t) = %ld", i64);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT64, (void **)&i64_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_FLOAT, (void **)&f_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT64, int64_t) = %ld", i64_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_FLOAT, float) = %lf", (double)f_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      // case (SMD_TYPE_FLOAT): {
      // float *p = (float *)out;
      //       case (SMD_TYPE_UINT32): {
      //         uint32_t ov = *(uint32_t*)val;
      //         *p = (float) ov;
      //         // check if accuracy is precise enough
      //         if(ov != (uint32_t)*p){
      //           return 1;
      //         }
      //         return 0;
      //       }

      printf("\n\nOriginal Type: FLOAT!");
      printf("\nStorage Type: UINT32!\n");

      printf("\nFrom GDB!");
      printf("\nOriginal number = %lu", ui32);
      printf("\nStored number = 4294967294");
      printf("\nRetrieved number = 0");
      printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

      smd_attr_t *attr1;

      attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_FLOAT, SMD_DTYPE_UINT32, &ui32, id);
      if (attr1 == NULL) {
        printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
      } else {
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(float, uint32_t) = %d", ui32);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_UINT32, (void **)&ui32_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_FLOAT, (void **)&f_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_UINT32, uint32_t) = %d", ui32_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_FLOAT, float) = %lf", (double)f_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      // case (SMD_TYPE_FLOAT): {
      // float *p = (float *)out;
      //       case (SMD_TYPE_UINT64): {
      //         uint64_t ov = *(uint64_t*)val;
      //         *p = (float) ov;
      //         // check if accuracy is precise enough
      //         if(ov != (uint64_t)*p){
      //           return 1;
      //         }
      //         return 0;
      //       }

      printf("\n\nOriginal Type: FLOAT!");
      printf("\nStorage Type: UINT64!\n");

      printf("\nFrom GDB!");
      printf("\nOriginal number = %lu", ui64);
      printf("\nStored number = 18446744073709551614");
      printf("\nRetrieved number = 9223372036854775807");
      printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

      smd_attr_t *attr1;

      attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_FLOAT, SMD_DTYPE_UINT64, &ui64, id);
      if (attr1 == NULL) {
        printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
      } else {
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(float, uint64_t) = %lu", ui64);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_UINT64, (void **)&ui64_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_FLOAT, (void **)&f_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_UINT64, uint64_t) = %lu", ui64_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_FLOAT, float) = %lf", (double)f_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      // case (SMD_TYPE_DOUBLE): {
      // double *p = (double *)out;
      //     case (SMD_TYPE_INT64): {
      //       int64_t ov = *(int64_t*)val;
      //       *p = (double) ov;
      //       // check if accuracy is precise enough
      //       if(ov != (int64_t)*p){
      //         return 1;
      //       }
      //       return 0;
      //     }

      printf("\n\nOriginal Type: DOUBLE!");
      printf("\nStorage Type: INT64!\n");

      printf("\nFrom GDB!");
      printf("\nOriginal number = %ld", i64);
      printf("\nStored number = -9223372036854775807");
      printf("\nRetrieved number = -9223372036854775808");

      smd_attr_t *attr1;

      attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_DOUBLE, SMD_DTYPE_INT64, &i64, id);
      if (attr1 == NULL) {
        printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
      } else {
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(double, int64_t) = %ld", i64);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT64, (void **)&i64_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT64, int64_t) = %ld", i64_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_DOUBLE, double) = %lf", d_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      // case (SMD_TYPE_DOUBLE): {
      // double *p = (double *)out;
      //     case (SMD_TYPE_UINT64): {
      //       uint64_t ov = *(uint64_t*)val;
      //       *p = (double) ov;
      //       // check if accuracy is precise enough
      //       if(ov != (uint64_t)*p){
      //         return 1;
      //       }
      //       return 0;
      //     }

      printf("\n\nOriginal Type: DOUBLE!");
      printf("\nStorage Type: UINT64!\n");

      printf("\nFrom GDB!");
      printf("\nOriginal number = %lu", ui64);
      printf("\nStored number = 18446744073709551614");
      printf("\nRetrieved number = 9223372036854775807");
      printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

      smd_attr_t *attr1;

      attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_DOUBLE, SMD_DTYPE_UINT64, &ui64, id);
      if (attr1 == NULL) {
        printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
      } else {
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(double, uint64_t) = %lu", ui64);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_UINT64, (void **)&ui64_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_UINT64, uint64_t) = %lu", ui64_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_DOUBLE, double) = %lf", d_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    {
      // case (SMD_TYPE_DOUBLE): {
      // double *p = (double *)out;
      // case (SMD_TYPE_FLOAT): {
      //   float ov = *(float*)val;
      //   *p = (double) ov;
      //   // check if accuracy is precise enough
      //   if(ov != (float)*p){
      //     return 1;
      //   }
      //   return 0;
      // }

      printf("\n\nOriginal Type: DOUBLE!");
      printf("\nStorage Type: FLOAT!\n");

      printf("\nWhat's a case when this won't work?");
      printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

      smd_attr_t *attr1;

      attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_DOUBLE, SMD_DTYPE_FLOAT, &f, id);
      if (attr1 == NULL) {
        printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
      } else {
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(double, float) = %f", (double)f);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_FLOAT, (void **)&f_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_DOUBLE, double) = %lf", d_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_FLOAT, float) = %f", (double)f_);

        smd_attr_destroy(attr1);
        smd_attr_unlink_pos(attr, 0);
      }
    }

    // **************************************************************************************

    // printf("\nCOPY TO EXTERNAL!\n");
    //
    // {

    // int32_t i32 = INT32_MIN + 1;
    // int64_t si32 = 2000000000;
    // float fi32 = 2000000000;
    // double di32 = 2000000000;
    //
    // int64_t i64 = INT64_MIN + 1;
    // float fi64 = 9000000000000000000;
    // double di64 = 9000000000000000000;
    //
    // int32_t ui32 = UINT32_MAX;
    // int64_t ui64 = UINT64_MAX;
    // double df = 1.0e35;
    // float f = 340282346638528859811704183484516000000.0;
    // double d = 340282346638528859811704183484516925430.12345;

    // float f = 2147480000.12345;

    // case (SMD_TYPE_INT32): {
    // int32_t *p = (int32_t *)val;
    //     case (SMD_TYPE_FLOAT): {
    //       float ov = (float)(*p);
    //       *(float *)out = ov;
    //       // check if accuracy is precise enough
    //       if((int32_t)ov != *p){
    //         printf("\nAccuracy is not precise enough!");
    //         printf("\nStored number = %d", *(int32_t*)val);
    //         printf("\nRetrieved number = %d\n", (int32_t)*p);
    //         return 1;
    //       }
    //       return 0;
    //     }

    //   printf("\n\nOriginal Type: INT32!");
    //   printf("\nStorage Type: FLOAT!\n");
    //
    //   printf("\nFrom GDB!");
    //   printf("\nOriginal number = %f", (double)f);
    //   printf("\nStored number = ");
    //   printf("\nRetrieved number = ");
    //
    //   printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    //
    //   printf("\nIt turns ");
    //
    //   smd_attr_t *attr1;
    //
    //   attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_INT32, SMD_DTYPE_FLOAT, &f, id);
    //   if (attr1 == NULL) {
    //     printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
    //   } else {
    //     ret = smd_attr_link(attr, attr1, 1);
    //     assert(ret == SMD_ATTR_LINKED);
    //
    //     printf("\nsmd_attr_new_usertype(int32_t, float) = %f", (double)f);
    //
    //     ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT32, (void **)&i32_);
    //     if (ret) {
    //       printf("\nSorry... Something is really messed up!!! :(\n");
    //     }
    //     ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_FLOAT, (void **)&f_);
    //     if (ret) {
    //       printf("\nSorry... Something is really messed up!!! :(\n");
    //     }
    //
    //     printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT32, int32_t) = %d", i32_);
    //     printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_FLOAT, float) = %f", (double)f_);
    //
    //     smd_attr_destroy(attr1);
    //     smd_attr_unlink_pos(attr, 0);
    //
    //   }
    // }
    //
    // {
    //
    //   // int32_t i32 = INT32_MIN + 1;
    //   // int64_t si32 = 2000000000;
    //   // float fi32 = 2000000000;
    //   // double di32 = 2000000000;
    //   //
    //   double d = 9223372036850000000;
    //   // float fi64 = 9000000000000000000;
    //   // double d = 9000000000000000000;
    //   //
    //   // int32_t ui32 = UINT32_MAX;
    //   // int64_t ui64 = UINT64_MAX;
    //   // double df = 1.0e35;
    //   // float f = 340282346638528859811704183484516000000.0;
    //   // double d = 340282346638528859811704183484516925430.12345;
    //
    //   // double df = 1.0e35;
    //   // float f = 340282346638528859811704183484516000000.0;
    //             // float f =    340282346638528859811704183484516925440;
    //   // double d = DBL_MAX - 1;
    //   // double d = 1.7e300;
    //   // double d = 340282346638528859811704183484516925430.12345;
    //
    //   // case (SMD_TYPE_INT32): {
    //   // int32_t *p = (int32_t *)val;
    //   //     case (SMD_TYPE_FLOAT): {
    //   //       float ov = (float)(*p);
    //   //       *(float *)out = ov;
    //   //       // check if accuracy is precise enough
    //   //       if((int32_t)ov != *p){
    //   //         printf("\nAccuracy is not precise enough!");
    //   //         printf("\nStored number = %d", *(int32_t*)val);
    //   //         printf("\nRetrieved number = %d\n", (int32_t)*p);
    //   //         return 1;
    //   //       }
    //   //       return 0;
    //   //     }
    //
    //   printf("\n\nOriginal Type: INT64!");
    //   printf("\nStorage Type: DOUBLE!\n");
    //
    //   printf("\nFrom GDB!");
    //   printf("\nOriginal number = %lf", d);
    //   printf("\nStored number = ");
    //   printf("\nRetrieved number = ");
    //
    //   printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    //
    //   printf("\nIt turns ");
    //
    //   smd_attr_t *attr1;
    //
    //   attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_INT64, SMD_DTYPE_DOUBLE, &d, id);
    //   if (attr1 == NULL) {
    //     printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
    //   } else {
    //     ret = smd_attr_link(attr, attr1, 1);
    //     assert(ret == SMD_ATTR_LINKED);
    //
    //     printf("\nsmd_attr_new_usertype(int64_t, double) = %lf", d);
    //
    //     ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT64, (void **)&i64_);
    //     if (ret) {
    //       printf("\nSorry... Something is really messed up!!! :(\n");
    //     }
    //     ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
    //     if (ret) {
    //       printf("\nSorry... Something is really messed up!!! :(\n");
    //     }
    //
    //     printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT64, int64_t) = %ld", i64_);
    //     printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_DOUBLE, double) = %lf", d_);
    //
    //     smd_attr_destroy(attr1);
    //     smd_attr_unlink_pos(attr, 0);
    //
    //   }
    // }
  }

  printf("\n\n\n");

  // **************************************************************************************

  return 0;
}
