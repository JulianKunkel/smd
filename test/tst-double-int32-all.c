#include <assert.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {

  printf("\n\nTesting INT32 to DOUBLE!\n");

  int32_t t;
  double d;

  printf("\nINT32_MAX = %d\n", INT32_MAX);

  for (int32_t i = 0; i < INT32_MAX; i++){
    d = t = INT32_MAX - i;
    if (d == INT32_MAX) {
      printf("\nFAILURE\n");
      printf("\nValue (double) = %lf", d);
      printf("\nReal Value (int32_t) = %d", t);
      printf("\nConverted Value (int32_t) = %d", (int32_t)d);
    } else {
      printf("\n\nSUCCESS\n");
      printf("\nValue (double) = %lf", d);
      printf("\nReal Value (int32_t) = %d", t);
      printf("\nConverted Value (int32_t) = %d\n", (int32_t)d);
      break;
    }
  }

  int32_t int32_max = t;
  double dbl_max = d;

  printf("\nINT32_MIN = %d\n", INT32_MIN);

  for (int32_t i = 0; i > INT32_MIN; i++){
    d = t = INT32_MIN + i;
    if (d == INT32_MIN) {
      printf("\nFAILURE\n");
      printf("\nValue (double) = %lf", d);
      printf("\nReal Value (int32_t) = %d", t);
      printf("\nConverted Value (int32_t) = %d", (int32_t)d);
    } else {
      printf("\n\nSUCCESS\n");
      printf("\nValue (double) = %lf", d);
      printf("\nReal Value (int32_t) = %d", t);
      printf("\nConverted Value (int32_t) = %d", (int32_t)d);
      break;
    }
  }

  int32_t int32_min = t;
  double dbl_min = d;

  printf("\n\n\nFinal Results - INT32 to DOUBLE\n\n");

  printf("********************************************");
  printf("\nINT32_MAX = %d", INT32_MAX);
  printf("\nMaximum DOUBLE = %lf", dbl_max);
  printf("\nMaximum INT32 = %d\n", int32_max);
  printf("********************************************");

  printf("\n\n");

  printf("********************************************");
  printf("\nINT32_MIN = %d", INT32_MIN);
  printf("\nMinimum DOUBLE = %lf", dbl_min);
  printf("\nMinimum INT32 = %d\n", int32_min);
  printf("********************************************");

  printf("\n\n");

  // **************************************************************************************

  return 0;
}
