#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

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

  printf("\nCOPY TO INTERNAL!\n");

  {
    int32_t i32 = 2000000000; // Changes to 9000000202358128640!
    int64_t i64 = 9000000000000000000; // Changes to 9000000202358128640!
    float f = 9000000000000000000; // Changes to 9000000202358128640!
    double d = 9000000000000000000; // Changes to 9000000202358128640!

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

      printf("\nOriginal Type: FLOAT!");
      printf("\nStorage Type: INT32!\n");

      printf("\nFrom GDB!\n");
      printf("\nOriginal number = %f", f);
      printf("\nStored number = 1593429209");
      printf("\nRetrieved number = 1593429248");

      smd_attr_t *attr1;

      attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_FLOAT, SMD_DTYPE_INT32, &f, id);
      if (attr1 == NULL) {
        printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
      } else {
        ret = smd_attr_link(attr, attr1, 1);
        assert(ret == SMD_ATTR_LINKED);

        printf("\nsmd_attr_new_usertype(int32_t, float) = %f", f);

        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT32, (void **)&i32_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }
        ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_DOUBLE, (void **)&f_);
        if (ret) {
          printf("\nSorry... Something is really messed up!!! :(\n");
        }

        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT32, int32_t) = %d", i32_);
        printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_FLOAT, float) = %lf", f_);

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


    printf("\nOriginal Type: FLOAT!");
    printf("\nStorage Type: INT64!\n");

    printf("\nFrom GDB!\n");
    printf("\nOriginal number = %f", f);
    printf("\nStored number = 1593429209");
    printf("\nRetrieved number = 1593429248");

    smd_attr_t *attr1;

    attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_FLOAT, SMD_DTYPE_INT64, &f, id);
    if (attr1 == NULL) {
      printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
    } else {
      ret = smd_attr_link(attr, attr1, 1);
      assert(ret == SMD_ATTR_LINKED);

      printf("\nsmd_attr_new_usertype(int64_t, float) = %f", f);

      ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT64, (void **)&i64_);
      if (ret) {
        printf("\nSorry... Something is really messed up!!! :(\n");
      }
      ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_DOUBLE, (void **)&f_);
      if (ret) {
        printf("\nSorry... Something is really messed up!!! :(\n");
      }

      printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT64, int64_t) = %d", i64_);
      printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_FLOAT, float) = %lf", f_);

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

  printf("\nOriginal Type: FLOAT!");
  printf("\nStorage Type: UINT32!\n");

  printf("\nFrom GDB!\n");
  printf("\nOriginal number = %f", f);
  printf("\nStored number = 1593429209");
  printf("\nRetrieved number = 1593429248");

  smd_attr_t *attr1;

  attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_FLOAT, SMD_DTYPE_UINT32, &f, id);
  if (attr1 == NULL) {
    printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
  } else {
    ret = smd_attr_link(attr, attr1, 1);
    assert(ret == SMD_ATTR_LINKED);

    printf("\nsmd_attr_new_usertype(uint32_t, float) = %f", f);

    ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_UINT32, (void **)&ui32_);
    if (ret) {
      printf("\nSorry... Something is really messed up!!! :(\n");
    }
    ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_DOUBLE, (void **)&f_);
    if (ret) {
      printf("\nSorry... Something is really messed up!!! :(\n");
    }

    printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_UINT32, uint32_t) = %d", ui32_);
    printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_FLOAT, float) = %lf", f_);

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

  printf("\nOriginal Type: FLOAT!");
  printf("\nStorage Type: UINT64!\n");

  printf("\nFrom GDB!\n");
  printf("\nOriginal number = %f", f);
  printf("\nStored number = 1593429209");
  printf("\nRetrieved number = 1593429248");

  smd_attr_t *attr1;

  attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_FLOAT, SMD_DTYPE_UINT64, &f, id);
  if (attr1 == NULL) {
    printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
  } else {
    ret = smd_attr_link(attr, attr1, 1);
    assert(ret == SMD_ATTR_LINKED);

    printf("\nsmd_attr_new_usertype(uint64_t, float) = %f", f);

    ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_UINT64, (void **)&ui64_);
    if (ret) {
      printf("\nSorry... Something is really messed up!!! :(\n");
    }
    ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_FLOAT, (void **)&f_);
    if (ret) {
      printf("\nSorry... Something is really messed up!!! :(\n");
    }

    printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_UINT64, uint64_t) = %d", ui64_);
    printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_FLOAT, float) = %lf", f_);

    smd_attr_destroy(attr1);
    smd_attr_unlink_pos(attr, 0);

  }
}

// {
//     // case (SMD_TYPE_INT64): {
//     // int64_t *p = (int64_t *)out;
//     //     case (SMD_TYPE_INT32): {
//     //       int32_t ov = *(int32_t*)val;
//     //       *p = (int64_t) ov;
//     //       // check if accuracy is precise enough
//     //       if((int64_t)ov != *p){
//     //         printf("\nAccuracy is not precise enough!");
//     //         printf("\nStored number = %ld", (int64_t)ov);
//     //         printf("\nRetrieved number = %ld\n", *p);
//     //         return 1;
//     //       }
//     //       return 0;
//     //     }
//
//   printf("\nOriginal Type: INT64!");
//   printf("\nStorage Type: INT32!\n");
//
//   printf("\nFrom GDB!\n");
//   printf("\nOriginal number = %ld", i64);
//   printf("\nStored number = ");
//   printf("\nRetrieved number = ");
//
//   smd_attr_t *attr1;
//
//   attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_INT32, SMD_DTYPE_INT64, &i64, id);
//   attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_INT64, SMD_DTYPE_INT32, &i64, id);
//
// // Which one is right?!
//
//   if (attr1 == NULL) {
//     printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
//   } else {
//     ret = smd_attr_link(attr, attr1, 1);
//     assert(ret == SMD_ATTR_LINKED);
//
//     printf("\nsmd_attr_new_usertype(int32_t, int64_t) = %ld", i64);
//
//     ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT32, (void **)&i32_);
//     if (ret) {
//       printf("\nSorry... Something is really messed up!!! :(\n");
//     }
//     ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_INT64, (void **)&i64_);
//     if (ret) {
//       printf("\nSorry... Something is really messed up!!! :(\n");
//     }
//
//     printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT32, int32_t) = %d", i32_);
//     printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_INT64, int64_t) = %ld", i64_);
//
//     smd_attr_destroy(attr1);
//     smd_attr_unlink_pos(attr, 0);
//
//   }
// }

{
  // case (SMD_TYPE_FLOAT): {
  // float *p = (float *)out;
  //       case (SMD_TYPE_DOUBLE): {
  //         double ov = *(double*)val;
  //         // check the range
  //         if(ov > 0 && (ov < (double)FLT_MIN || ov > (double)FLT_MAX)){
  //           return 1;
  //         }
  //         if(ov < 0 && (ov > -(double)FLT_MIN || ov < -(double)FLT_MAX)){
  //           return 1;
  //         }
  //         *p = (float) ov;
  //         // check if accuracy is precise enough
  //         if(ov != (float)*p){
  //           return 1;
  //         }
  //         return 0;
  //       }

  float f2 = 100;

  printf("\nRed Alert! Red Alert! Red Alert! Red Alert!\n");

  printf("\nOriginal Type: FLOAT!");
  printf("\nStorage Type: DOUBLE!\n");

  printf("\nFrom GDB!\n");
  printf("\nOriginal number = %f", f2);
  printf("\n*(float*)val = 100");
  printf("\n(double)*(float*)val = 100");
  printf("\n*(double*)val = 7.8725863124689162e-315");

  printf("\n\nIt stops because of this test: if(ov > 0 && (ov < (double)FLT_MIN || ov > (double)FLT_MAX)");

  printf("\n\nIt doesn't reach the accuracy check. I'm not even sure this test is necessary in this case.");

  smd_attr_t *attr1;

  attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_FLOAT, SMD_DTYPE_DOUBLE, &f2, id);
  if (attr1 == NULL) {
    printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
  } else {
    ret = smd_attr_link(attr, attr1, 1);
    assert(ret == SMD_ATTR_LINKED);

    printf("\nsmd_attr_new_usertype(int8_t, double) = %f", f2);

    ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
    if (ret) {
      printf("\nSorry... Something is really messed up!!! :(\n");
    }
    ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_FLOAT, (void **)&f_);
    if (ret) {
      printf("\nSorry... Something is really messed up!!! :(\n");
    }

    printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_DOUBLE, double) = %lf", d_);
    printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_FLOAT, float) = %f", f_);

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

  printf("\nOriginal Type: DOUBLE!");
  printf("\nStorage Type: INT64!\n");

  printf("\nFrom GDB!\n");
  printf("\nOriginal number = %lf", d);
  printf("\nStored number = 4890691058569617664");
  printf("\nRetrieved number = 4890691058569617408");

  smd_attr_t *attr1;

  attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_DOUBLE, SMD_DTYPE_INT64, &d, id);
  if (attr1 == NULL) {
    printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
  } else {
    ret = smd_attr_link(attr, attr1, 1);
    assert(ret == SMD_ATTR_LINKED);

    printf("\nsmd_attr_new_usertype(int64_t, double) = %lf", d);

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

  printf("\nOriginal Type: DOUBLE!");
  printf("\nStorage Type: UINT64!\n");

  printf("\nFrom GDB!\n");
  printf("\nOriginal number = %lf", d);
  printf("\nStored number = 4890691058569617664");
  printf("\nRetrieved number = 4890691058569617408");

  smd_attr_t *attr1;

  attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_DOUBLE, SMD_DTYPE_UINT64, &d, id);
  if (attr1 == NULL) {
    printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
  } else {
    ret = smd_attr_link(attr, attr1, 1);
    assert(ret == SMD_ATTR_LINKED);

    printf("\nsmd_attr_new_usertype(uint64_t, double) = %lf", d);

    ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_UINT64, (void **)&ui64_);
    if (ret) {
      printf("\nSorry... Something is really messed up!!! :(\n");
    }
    ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
    if (ret) {
      printf("\nSorry... Something is really messed up!!! :(\n");
    }

    printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_UINT64, uint64_t) = %ld", ui64_);
    printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_DOUBLE, double) = %lf", d_);

    smd_attr_destroy(attr1);
    smd_attr_unlink_pos(attr, 0);

  }
}

// **************************************************************************************

// printf("\nCOPY TO EXTERNAL!\n");

// {
//       // case (SMD_TYPE_INT32): {
//       // int32_t *p = (int32_t *)val;
//       //     case (SMD_TYPE_UINT32): {
//       //       uint32_t ov = (uint32_t)(*p);
//       //       *(uint32_t *)out = ov;
//       //       // check if accuracy is precise enough
//       //       if((int32_t)ov != *p){
//       //         return 1;
//       //       }
//       //       return 0;
//       //     }
//
//   printf("\nOriginal Type: UINT64!");
//   printf("\nStorage Type: DOUBLE!\n");
//
//   printf("\nFrom GDB!\n");
//   printf("\nOriginal number = %lf", d);
//   printf("\nStored number = 4890691058569617664");
//   printf("\nRetrieved number = 4890691058569617408");
//
//   smd_attr_t *attr1;
//
//   attr1 = smd_attr_new_usertype(buff, SMD_DTYPE_DOUBLE, SMD_DTYPE_UINT64, &d, id);
//   if (attr1 == NULL) {
//     printf("\n\nSorry... It's not possible to make this conversion! :(\n\n");
//   } else {
//     ret = smd_attr_link(attr, attr1, 1);
//     assert(ret == SMD_ATTR_LINKED);
//
//     printf("\nsmd_attr_new_usertype(uint64_t, double) = %lf", d);
//
//     ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_UINT64, (void **)&ui64_);
//     if (ret) {
//       printf("\nSorry... Something is really messed up!!! :(\n");
//     }
//     ret = smd_attr_copy_value_usertype(attr1, SMD_DTYPE_DOUBLE, (void **)&d_);
//     if (ret) {
//       printf("\nSorry... Something is really messed up!!! :(\n");
//     }
//
//     printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_UINT64, uint64_t) = %ld", ui64_);
//     printf("\nsmd_attr_copy_value_usertype(SMD_DTYPE_DOUBLE, double) = %lf", d_);
//
//     smd_attr_destroy(attr1);
//     smd_attr_unlink_pos(attr, 0);
//
//   }
// }

}

  // **************************************************************************************

  return 0;
}
