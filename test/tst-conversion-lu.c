#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

#define make_conversion(smd_type, smd_usertype, var_type, var_usertype, format_type, format_usertype, a, b, value_usertype)      \
                                                                                                      \
char buff[100];                                                                                       \
strcpy(buff, "child");                                                                                \
int i = 0, j = 0;                                                                                     \
{                                                                                                     \
                                                                                                      \
  smd_attr_t *attr1 = smd_attr_new_usertype(buff, smd_type, smd_usertype, &value_usertype);       \
  if (attr1 == NULL) {                                                                                \
    conv[j++][i] = 0;                                                                                 \
    printf("\nSorry... It's not possible to make this conversion! :(");                               \
  } else {                                                                                            \
    conv[j++][i] = 1;                                                                                 \
    ret = smd_attr_link(attr, attr1, 1);                                                              \
    assert(ret == SMD_ATTR_LINKED);                                                                   \
                                                                                                      \
    ret = smd_attr_copy_value_usertype(attr1, smd_type, (void **)&var_type);                          \
    if (ret) {                                                                                        \
      printf("\nSorry... Something is really messed up!!! :(");                                       \
    }                                                                                                 \
    ret = smd_attr_copy_value_usertype(attr1, smd_usertype, (void **)&var_usertype);                  \
    if (ret) {                                                                                        \
      printf("\nSorry... Something is really messed up!!! :(");                                       \
    }                                                                                                 \
                                                                                                      \
    printf("\nStored as %6s =\t"format_type"", types[a], var_type);                                   \
    printf("\nStored as %6s =\t"format_usertype"", types[b], var_usertype);                           \
                                                                                                      \
    smd_attr_destroy(attr1);                                                                          \
    smd_attr_unlink_pos(attr, 0);                                                                     \
  }                                                                                                   \
}                                                                                                     \

int main() {

  int id = 0;
  int ret;

  char *name = "SMD Test for Conversions";
  smd_attr_t *attr = smd_attr_new("root", SMD_DTYPE_STRING, name);
  char *ptr = (char *)16;
  smd_attr_copy_value(attr, &ptr);
  assert(strcmp(ptr, "SMD Test for Conversions") == 0);

  char types[11][10] = {"INT8", "INT16", "INT32", "INT64", "UINT8", "UINT16", "UINT32", "UINT64", "FLOAT", "DOUBLE", "CHAR"};
  // char types[11][10] = {"0",   "1",     "2",     "3",     "4",     "5",      "6",      "7",       "8",     "9",    "10"};
  smd_dtype_t * smd_types[11] = {SMD_DTYPE_INT8, SMD_DTYPE_INT16, SMD_DTYPE_INT32, SMD_DTYPE_INT64, SMD_DTYPE_UINT8, SMD_DTYPE_UINT16, SMD_DTYPE_UINT32, SMD_DTYPE_UINT64, SMD_DTYPE_FLOAT, SMD_DTYPE_DOUBLE, SMD_DTYPE_CHAR};

  printf("\n\n*************************************************************************************");

  printf("\n\nSMD Test for Conversions");

  printf("\n\n*************************************************************************************\n");

  int n_int32 = 8;
  int32_t i32[8] = {-2000000000, -240, -120, 120, 240, 30000, 60000, 2000000000};
  int32_t i32_ = 0;
  int16_t i16_= 0;
  int conv[n_int32][11]; // Not used properly
  int a, b, t;

  a = 1;
  b = 2;
  printf("\nOriginal Type:     %10s!", types[a]);
  printf("\nUser-Defined Type: %10s!", types[b]);
  for (t = 0; t < n_int32; t++){
    printf("\n\nValue = %d", i32[t]);
    make_conversion(smd_types[1], smd_types[2], i16_, i32_, "%d", "%d", a, b, i32[t]);
  }

  printf("\n\n*************************************************************************************\n");

  int n_uint64 = 8;
  int64_t ui64[8] = {0, 120, 240, 30000, 60000, 2000000000, 9000000000000000000, UINT64_MAX};
  int64_t ui64_ = 0;
  float f_= 0;

  a = 8;
  b = 7;
  printf("\nOriginal Type:     %10s!", types[a]);
  printf("\nUser-Defined Type: %10s!", types[b]);
  for (t = 0; t < n_uint64; t++){
    printf("\n\nValue = %lu", ui64[t]);
    make_conversion(smd_types[8], smd_types[7], f_, ui64_, "%f", "%lu", a, b, ui64[t]);
  }

  printf("\n\n*************************************************************************************\n");

  return 0;
}
