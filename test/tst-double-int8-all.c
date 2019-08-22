#include <assert.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {

  printf("\nTesting INT8 to DOUBLE!\n");

  int8_t t;
  double d;

  printf("\nINT8_MAX = %d\n", INT8_MAX);

  for (int8_t i = 0; i < INT8_MAX; i++){
    d = t = INT8_MAX - i;
    if (d == INT8_MAX) {
      printf("\nFAILURE\n");
      printf("\nValue (double) = %lf", d);
      printf("\nReal Value (int8_t) = %d", t);
      printf("\nConverted Value (int8_t) = %d", (int8_t)d);
    } else {
      printf("\n\nSUCCESS\n");
      printf("\nValue (double) = %lf", d);
      printf("\nReal Value (int8_t) = %d", t);
      printf("\nConverted Value (int8_t) = %d", (int8_t)d);
      break;
    }
  }

  int8_t int8_max = t;
  double dbl_max = d;

  printf("\nINT8_MIN = %d\n", INT8_MIN);

  for (int8_t i = 0; i > INT8_MIN; i++){
    d = t = INT8_MIN + i;
    if (d == INT8_MIN) {
      printf("\nFAILURE\n");
      printf("\nValue (double) = %lf", d);
      printf("\nReal Value (int8_t) = %d", t);
      printf("\nConverted Value (int8_t) = %d", (int8_t)d);
    } else {
      printf("\n\nSUCCESS\n");
      printf("\nValue (double) = %lf", d);
      printf("\nReal Value (int8_t) = %d", t);
      printf("\nConverted Value (int8_t) = %d", (int8_t)d);
      break;
    }
  }

  int8_t int8_min = t;
  double dbl_min = d;

  printf("\n\n\nFinal Results - INT8 to DOUBLE\n\n");

  printf("********************************************");
  printf("\nINT8_MAX = %d", INT8_MAX);
  printf("\nMaximum DOUBLE = %lf", dbl_max);
  printf("\nMaximum INT8 = %d\n", int8_max);
  printf("********************************************");

  printf("\n\n");

  printf("********************************************");
  printf("\nINT8_MIN = %d", INT8_MIN);
  printf("\nMinimum DOUBLE = %lf", dbl_min);
  printf("\nMinimum INT8 = %d\n", int8_min);
  printf("********************************************");

  printf("\n\n");

  // **************************************************************************************

  return 0;
}
