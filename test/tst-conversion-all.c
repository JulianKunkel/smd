#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include <smd.h>
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#pragma GCC diagnostic ignored "-Wfloat-equal"

#define check_conversion_err(smd_type, smd_usertype, var_usertype, value)                           \
{                                                                                                   \
  var_usertype orig = value;                                                                        \
  smd_attr_t *attr1 = smd_attr_new_usertype("tst", smd_type, smd_usertype, & orig, 1);              \
  if (attr1 != NULL) {                                                                              \
    printf("\nSorry... The conversion "#smd_type" <- "#smd_usertype" shouldn't have worked\n");                                                 \
    exit(1);                                                                                        \
  }                                                                                                 \
}

#define make_conversion(smd_type, smd_usertype, var_type, var_usertype, value, format_type, format_usertype, expected1, expected2)      \
{                                                                                                   \
  var_usertype orig = value;                                                                        \
  printf("Check conversion "#smd_type" <- "#smd_usertype);                                        \
  smd_attr_t *attr1 = smd_attr_new_usertype("tst", smd_type, smd_usertype, & orig, 1);              \
  if (attr1 == NULL) {                                                                              \
    printf(" Error1\n");                                                                            \
    exit(1);                                                                                        \
  }                                                                                                 \
  ret = smd_attr_copy_value_usertype(attr1, smd_usertype, &orig);                                   \
  if (ret) {                                                                                        \
    printf(" Error2\n");                                                                            \
    exit(1);                                                                                        \
  }                                                                                                 \
  var_type stored;                                                                                  \
  ret = smd_attr_copy_value_usertype(attr1, smd_type, & stored);                                    \
  if (ret) {                                                                                        \
    printf(" Error3\n");                                                                            \
    exit(1);                                                                                        \
  }                                                                                                 \
                                                                                                    \
  printf(" stored \t"format_type" and "format_usertype, stored, orig);                         \
  if( orig != expected1 || stored != expected2){                                                    \
    printf(" Error, expected: \t"format_type" and "format_usertype"\n", expected2,                expected1);                                                                                     \
    exit(1);                                                                                        \
  }else{ printf(" OK\n"); }                                                                            \
  smd_attr_destroy(attr1);                                                                          \
}                                                                                                   \

int main() {

  int ret;
  printf("\n\n*************************************************************************************");
  printf("\n\nSMD Test for Conversions");
  printf("\n\n*************************************************************************************\n");

  check_conversion_err(SMD_DTYPE_FLOAT, SMD_DTYPE_UINT64, uint64_t, UINT64_MAX);
  check_conversion_err(SMD_DTYPE_FLOAT, SMD_DTYPE_UINT32, uint32_t, UINT32_MAX);
  check_conversion_err(SMD_DTYPE_FLOAT, SMD_DTYPE_DOUBLE, double, FLT_MAX);

  make_conversion(SMD_DTYPE_FLOAT, SMD_DTYPE_UINT64, float, uint64_t, 20000, "%f", "%lu", 20000lu, 20000.0);
  make_conversion(SMD_DTYPE_FLOAT, SMD_DTYPE_UINT64, float, uint64_t, 300000, "%f", "%lu", 300000lu, 300000.0);
  make_conversion(SMD_DTYPE_FLOAT, SMD_DTYPE_DOUBLE, float, double, 300000.0, "%f", "%f", 300000.0, 300000.0);
  make_conversion(SMD_DTYPE_FLOAT, SMD_DTYPE_DOUBLE, float, double, FLT_MAX/2, "%f", "%f", FLT_MAX/2, FLT_MAX/2);
  return 0;
}
