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
  double f;

  printf("\nINT32_MAX = %d\n\n", INT32_MAX);

  for (int32_t i = 0; i < INT32_MAX; i++){
    f = t = INT32_MAX - i;
    if (f == INT32_MAX) {
      // printf("\nFAILURE ");
      // printf("\nValue (float) = %lf", f);
      // printf("\nValue (int32_t) = %ld\n", t);
    } else {
      printf("\nSUCCESS");
      printf("\nValue = %lf", f);
      printf("\nValue = %d\n", t);
      break;
    }
  }

  int32_t int32_max = t;
  double dbl_max = f;

  printf("\n\n\nINT32_MIN = %d\n\n", INT32_MIN);

  for (int32_t i = 0; i > INT32_MIN; i++){
    f = t = INT32_MIN + i;
    if (f == INT32_MIN) {
      // printf("\nFAILURE ");
      // printf("\nValue (float) = %lf", f);
      // printf("\nValue (int32_t) = %ld\n", t);
    } else {
      printf("\nSUCCESS");
      printf("\nValue = %lf", f);
      printf("\nValue = %d\n", t);
      break;
    }
  }

  int32_t int32_min = t;
  double dbl_min = f;

  printf("\n\nFinal Results - INT32 to DOUBLE\n\n");

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
