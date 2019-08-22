#include <assert.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {

  printf("\n\nTesting INT64 to FLOAT!\n");

  int64_t t;
  float f;

  printf("\nINT64_MAX = %ld\n", INT64_MAX);

  printf("\nFAILURE\n");

  // for (int64_t i = 0; i < INT64_MAX; i++){
  for (int64_t i = 0; i < INT64_MAX; i+=10000){
    f = t = INT64_MAX - i;
    if (f == INT64_MAX) {
      // printf("\nFAILURE");
      // printf("\nValue (float) = %f", (double)f);
      // printf("\nReal Value (int64_t) = %ld", t);
      // printf("\nConverted Value (int64_t) = %ld", (int64_t)f);
    } else {
      printf("\nSUCCESS\n");
      printf("\nValue (float) = %f", (double)f);
      printf("\nReal Value (int64_t) = %ld", t);
      printf("\nConverted Value (int64_t) = %ld\n", (int64_t)f);
      break;
    }
  }

  int64_t int64_max = t;
  float flt_max = f;

  printf("\nINT64_MIN = %ld\n", INT64_MIN);

  printf("\nFAILURE\n");

  // for (int64_t i = 0; i > INT64_MIN; i++){
  for (int64_t i = 0; i > INT64_MIN; i+=10000){
    f = t = INT64_MIN + i;
    if (f == INT64_MIN) {
      // printf("\nFAILURE");
      // printf("\nValue (float) = %f", (double)f);
      // printf("\nReal Value (int64_t) = %ld", t);
      // printf("\nConverted Value (int64_t) = %ld", (int64_t)f);
    } else {
      printf("\nSUCCESS\n");
      printf("\nValue (float) = %f", (double)f);
      printf("\nReal Value (int64_t) = %ld", t);
      printf("\nConverted Value (int64_t) = %ld\n", (int64_t)f);
      break;
    }
  }

  int64_t int64_min = t;
  float flt_min = f;

  printf("\n\nFinal Results - INT64 to FLOAT\n\n");

  printf("********************************************");
  printf("\nINT64_MAX = %ld", INT64_MAX);
  printf("\nMaximum FLOAT = %f", (double)flt_max);
  printf("\nMaximum INT64 = %ld\n", int64_max);
  printf("********************************************");

  printf("\n\n");

  printf("********************************************");
  printf("\nINT64_MIN = %ld", INT64_MIN);
  printf("\nMinimum FLOAT = %f", (double)flt_min);
  printf("\nMinimum INT64 = %ld\n", int64_min);
  printf("********************************************");

  printf("\n\n");

  // **************************************************************************************

  return 0;
}
