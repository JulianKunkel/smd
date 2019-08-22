#include <assert.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {

  printf("\n\nTesting INT64 to DOUBLE!\n");

  int64_t t;
  double d;

  printf("\nINT64_MAX = %ld\n\n", INT64_MAX);

  printf("\nFAILURE\n");

  for (int64_t i = 0; i < INT64_MAX; i++){
    d = t = INT64_MAX - i;
    if (d == INT64_MAX) {
      // printf("\nFAILURE");
      // printf("\nValue (double) = %lf", d);
      // printf("\nReal Value (int64_t) = %ld", t);
      printf("\nConverted Value (int64_t) = %ld", (int64_t)d);
    } else {
      printf("\n\nSUCCESS\n");
      printf("\nValue (double) = %lf", d);
      printf("\nReal Value (int64_t) = %ld", t);
      printf("\nConverted Value (int64_t) = %ld", (int64_t)d);
      break;
    }
  }

  int64_t int64_max = t;
  double dbl_max = d;

  printf("\n\n\nINT64_MIN = %ld\n\n", INT64_MIN);

  printf("\nFAILURE\n");

  for (int64_t i = 0; i > INT64_MIN; i++){
    d = t = INT64_MIN + i;
    if (d == INT64_MIN) {
      // printf("\nFAILURE");
      // printf("\nValue (double) = %lf", d);
      // printf("\nReal Value (int64_t) = %d", t);
      printf("\nConverted Value (int64_t) = %ld", (int64_t)d);
    } else {
      printf("\n\nSUCCESS\n");
      printf("\nValue (double) = %lf", d);
      printf("\nReal Value (int64_t) = %ld", t);
      printf("\nConverted Value (int64_t) = %ld", (int64_t)d);
      break;
    }
  }

  int64_t int64_min = t;
  double dbl_min = d;

  printf("\n\n\nFinal Results - INT64 to DOUBLE\n\n");

  printf("********************************************");
  printf("\nINT64_MAX = %ld", INT64_MAX);
  printf("\nMaximum DOUBLE = %lf", dbl_max);
  printf("\nMaximum INT64 = %ld\n", int64_max);
  printf("********************************************");

  printf("\n\n");

  printf("********************************************");
  printf("\nINT64_MIN = %ld", INT64_MIN);
  printf("\nMinimum DOUBLE = %lf", dbl_min);
  printf("\nMinimum INT64 = %ld\n", int64_min);
  printf("********************************************");

  printf("\n\n");

  // **************************************************************************************

  return 0;
}
