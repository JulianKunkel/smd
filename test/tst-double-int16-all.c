#include <assert.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {

  printf("\n\nTesting INT16 to DOUBLE!\n");

  int16_t t;
  double d;

  printf("\nINT16_MAX = %d\n", INT16_MAX);

  for (int16_t i = 0; i < INT16_MAX; i++){
    d = t = INT16_MAX - i;
    if (d == INT16_MAX) {
      printf("\nFAILURE\n");
      printf("\nValue (double) = %lf", d);
      printf("\nReal Value (int16_t) = %d", t);
      printf("\nConverted Value (int16_t) = %d", (int16_t)d);
    } else {
      printf("\n\nSUCCESS\n");
      printf("\nValue (double) = %lf", d);
      printf("\nReal Value (int16_t) = %d", t);
      printf("\nConverted Value (int16_t) = %d", (int16_t)d);
      break;
    }
  }

  int16_t int16_max = t;
  double dbl_max = d;

  printf("\nINT16_MIN = %d\n", INT16_MIN);

  for (int16_t i = 0; i > INT16_MIN; i++){
    d = t = INT16_MIN + i;
    if (d == INT16_MIN) {
      printf("\nFAILURE\n");
      printf("\nValue (double) = %lf", d);
      printf("\nReal Value (int16_t) = %d", t);
      printf("\nConverted Value (int16_t) = %d", (int16_t)d);
    } else {
      printf("\n\nSUCCESS\n");
      printf("\nValue (double) = %lf", d);
      printf("\nReal Value (int16_t) = %d", t);
      printf("\nConverted Value (int16_t) = %d", (int16_t)d);
      break;
    }
  }

  int16_t int16_min = t;
  double dbl_min = d;

  printf("\n\n\nFinal Results - INT16 to DOUBLE\n\n");

  printf("********************************************");
  printf("\nINT16_MAX = %d", INT16_MAX);
  printf("\nMaximum DOUBLE = %lf", dbl_max);
  printf("\nMaximum INT16 = %d\n", int16_max);
  printf("********************************************");

  printf("\n\n");

  printf("********************************************");
  printf("\nINT16_MIN = %d", INT16_MIN);
  printf("\nMinimum DOUBLE = %lf", dbl_min);
  printf("\nMinimum INT16 = %d\n", int16_min);
  printf("********************************************");

  printf("\n\n");

  // **************************************************************************************

  return 0;
}
