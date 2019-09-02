#include <stdio.h>
#include <stdlib.h>

#include <assert.h>
#include <stdint.h>
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
    printf("\nSorry... The conversion "#smd_type" <- "#smd_usertype" shouldn't have worked\n");     \
    exit(1);                                                                                        \
  }                                                                                                 \
}                                                                                                   \

#define make_conversion(smd_type, smd_usertype, var_type, var_usertype, value, format_type, format_usertype, expected1, expected2)                                                                                                  \
{                                                                                                           \
  var_usertype orig = value;                                                                                \
  printf(#smd_type" <- "#smd_usertype);                                                  \
  smd_attr_t *attr1 = smd_attr_new_usertype("tst", smd_type, smd_usertype, & orig, 1);                      \
  if (attr1 == NULL) {                                                                                      \
    printf(" Error1\n");                                                                                    \
    exit(1);                                                                                                \
  }                                                                                                         \
  ret = smd_attr_copy_value_usertype(attr1, smd_usertype, &orig);                                           \
  if (ret) {                                                                                                \
    printf(" Error2\n");                                                                                    \
    exit(1);                                                                                                \
  }                                                                                                         \
  var_type stored;                                                                                          \
  ret = smd_attr_copy_value_usertype(attr1, smd_type, & stored);                                            \
  if (ret) {                                                                                                \
    printf(" Error3\n");                                                                                    \
    exit(1);                                                                                                \
  }                                                                                                         \
                                                                                                            \
  printf(" stored \t"format_type" and "format_usertype" expected: "format_type, stored, orig, expected2);   \
  if( orig != expected1 || stored != expected2){                                                            \
    printf(" Error, expected: \t"format_type" and "format_usertype"\n", expected2, expected1);              \
    exit(1);                                                                                                \
  }else{ printf(" OK\n"); }                                                                                 \
  smd_attr_destroy(attr1);                                                                                  \
}                                                                                                           \

int main() {

  int ret;
  printf("\n*************************************************************************************");
  printf("\n\nSMD Check Conversions");
  printf("\n\n*************************************************************************************\n\n");

  make_conversion(SMD_DTYPE_INT8, SMD_DTYPE_FLOAT, int8_t, float, 127, "%d", "%f", 127.0, 127);
  check_conversion_err(SMD_DTYPE_INT16, SMD_DTYPE_UINT16, uint16_t, 65535);
  check_conversion_err(SMD_DTYPE_INT32, SMD_DTYPE_UINT32, uint32_t, UINT32_MAX);
  check_conversion_err(SMD_DTYPE_INT64, SMD_DTYPE_FLOAT, float, INT64_MAX);

  check_conversion_err(SMD_DTYPE_UINT8, SMD_DTYPE_INT8, int8_t, -1);
  check_conversion_err(SMD_DTYPE_UINT16, SMD_DTYPE_FLOAT, float, 65536.0f);
  make_conversion(SMD_DTYPE_UINT16, SMD_DTYPE_FLOAT, uint16_t, float, 65535.0f, "%u", "%.16e", 65535.0, 65535);
  make_conversion(SMD_DTYPE_UINT32, SMD_DTYPE_INT32, uint32_t, int32_t, INT32_MAX, "%u", "%d", INT32_MAX, INT32_MAX);
  check_conversion_err(SMD_DTYPE_UINT64, SMD_DTYPE_INT64, int64_t, -1);
  check_conversion_err(SMD_DTYPE_UINT64, SMD_DTYPE_FLOAT, float, 18446744073709551615.0f);
  make_conversion(SMD_DTYPE_UINT64, SMD_DTYPE_FLOAT, uint64_t, float, 9223372036854775808.0f, "%lu", "%.16e", 9.2233720368547758e+18, 9223372036854775808lu);

  check_conversion_err(SMD_DTYPE_FLOAT, SMD_DTYPE_INT32, int32_t, INT32_MAX);
  check_conversion_err(SMD_DTYPE_FLOAT, SMD_DTYPE_INT32, int32_t, INT32_MIN+1);
  check_conversion_err(SMD_DTYPE_FLOAT, SMD_DTYPE_UINT32, uint32_t, UINT32_MAX);
  make_conversion(SMD_DTYPE_FLOAT, SMD_DTYPE_INT32, float, int32_t, INT32_MIN, "%e", "%d", INT32_MIN, -2147483648.0f);
  make_conversion(SMD_DTYPE_FLOAT, SMD_DTYPE_INT32, float, int32_t, 21474800, "%e", "%d", 21474800, 21474800.0f);
  check_conversion_err(SMD_DTYPE_FLOAT, SMD_DTYPE_UINT64, uint64_t, UINT64_MAX);
  check_conversion_err(SMD_DTYPE_FLOAT, SMD_DTYPE_DOUBLE, double, FLT_MAX*1.0000001);
  check_conversion_err(SMD_DTYPE_FLOAT, SMD_DTYPE_DOUBLE, double, FLT_MIN*0.999999);
  make_conversion(SMD_DTYPE_FLOAT, SMD_DTYPE_DOUBLE, float, double, FLT_MAX, "%e", "%e", FLT_MAX, (double) FLT_MAX);
  make_conversion(SMD_DTYPE_FLOAT, SMD_DTYPE_DOUBLE, float, double, FLT_MIN, "%e", "%e", FLT_MIN, (double) FLT_MIN);
  check_conversion_err(SMD_DTYPE_FLOAT, SMD_DTYPE_UINT64, uint64_t, 4611686018427387903lu);
  make_conversion(SMD_DTYPE_FLOAT, SMD_DTYPE_UINT64, float, uint64_t, 4611686018427387904lu, "%e", "%lu", 4611686018427387904lu, 4611686018427387904.0);
  make_conversion(SMD_DTYPE_FLOAT, SMD_DTYPE_UINT64, float, uint64_t, 300000, "%e", "%lu", 300000lu, 300000.0);
  make_conversion(SMD_DTYPE_FLOAT, SMD_DTYPE_DOUBLE, float, double, 300000.0, "%e", "%e", 300000.0, 300000.0);

  make_conversion(SMD_DTYPE_DOUBLE, SMD_DTYPE_INT16, double, int16_t, 32767, "%f", "%d", 32767, 32767.0);
  make_conversion(SMD_DTYPE_DOUBLE, SMD_DTYPE_INT32, double, int32_t, 2147483647, "%f", "%d", 2147483647, 2147483647.0);
  check_conversion_err(SMD_DTYPE_DOUBLE, SMD_DTYPE_INT64, int64_t, INT64_MAX);
  check_conversion_err(SMD_DTYPE_DOUBLE, SMD_DTYPE_UINT64, uint64_t, UINT64_MAX);

  // These tests are basically done by the compiler conversion, added for testing the sanity of them
  make_conversion(SMD_DTYPE_FLOAT, SMD_DTYPE_DOUBLE, float, double, 1000000000000000000000000000000000000.0f, "%.16e", "%.16e",9.9999996169031625e+35f, 9.9999996169031625e+35);
  make_conversion(SMD_DTYPE_DOUBLE, SMD_DTYPE_FLOAT, double, float, 1000000000000000000000000000000000000.0, "%.16e", "%.16e", 9.9999996169031625e+35f, 9.9999996169031625e+35);
  make_conversion(SMD_DTYPE_DOUBLE, SMD_DTYPE_DOUBLE, double, double, 1000000000000000000000000000000000000.0, "%.16e", "%.16e", 1000000000000000000000000000000000000.0, 1000000000000000000000000000000000000.0);

  printf("All OK\n");

  return 0;
}
