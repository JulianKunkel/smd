#include <assert.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {

  printf("\n\nTesting INT8 to FLOAT!\n");

  int8_t t;
  float f;

  printf("\nINT8_MAX = %d\n", INT8_MAX);

  for (int8_t i = 0; i < INT8_MAX; i++){
    f = t = INT8_MAX - i;
    if (f == INT8_MAX) {
      printf("\nFAILURE\n");
      printf("\nValue (float) = %f", (double)f);
      printf("\nReal Value (int8_t) = %d", t);
      printf("\nConverted Value (int8_t) = %d\n", (int8_t)f);
    } else {
      printf("\nSUCCESS\n");
      printf("\nValue (float) = %f", (double)f);
      printf("\nReal Value (int8_t) = %d", t);
      printf("\nConverted Value (int8_t) = %d\n", (int8_t)f);
      break;
    }
  }

  int8_t int8_max = t;
  float flt_max = f;

  printf("\nINT8_MIN = %d\n", INT8_MIN);

  for (int8_t i = 0; i > INT8_MIN; i++){
    f = t = INT8_MIN + i;
    if (f == INT8_MIN) {
      printf("\nFAILURE\n");
      printf("\nValue (float) = %f", (double)f);
      printf("\nReal Value (int8_t) = %d", t);
      printf("\nConverted Value (int8_t) = %d\n", (int8_t)f);
    } else {
      printf("\nSUCCESS\n");
      printf("\nValue (float) = %f", (double)f);
      printf("\nReal Value (int8_t) = %d", t);
      printf("\nConverted Value (int8_t) = %d\n", (int8_t)f);
      break;
    }
  }

  int8_t int8_min = t;
  float flt_min = f;

  printf("\n\nFinal Results - INT8 to FLOAT\n\n");

  printf("********************************************");
  printf("\nINT8_MAX = %d", INT8_MAX);
  printf("\nMaximum FLOAT = %f", (double)flt_max);
  printf("\nMaximum INT8 = %d\n", int8_max);
  printf("********************************************");

  printf("\n\n");

  printf("********************************************");
  printf("\nINT8_MIN = %d", INT8_MIN);
  printf("\nMinimum FLOAT = %f", (double)flt_min);
  printf("\nMinimum INT8 = %d\n", int8_min);
  printf("********************************************");

  printf("\n\n");

  // **************************************************************************************

  return 0;
}
