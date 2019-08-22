#include <assert.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {

  printf("\n\nTesting INT16 to FLOAT!\n");

  int16_t t;
  float f;

  printf("\nINT16_MAX = %d\n", INT16_MAX);

  for (int16_t i = 0; i < INT16_MAX; i++){
    f = t = INT16_MAX - i;
    if (f == INT16_MAX) {
      printf("\nFAILURE\n");
      printf("\nValue (float) = %f", (double)f);
      printf("\nReal Value (int16_t) = %d", t);
      printf("\nConverted Value (int16_t) = %d\n", (int16_t)f);
    } else {
      printf("\nSUCCESS\n");
      printf("\nValue (float) = %f", (double)f);
      printf("\nReal Value (int16_t) = %d", t);
      printf("\nConverted Value (int16_t) = %d\n", (int16_t)f);
      break;
    }
  }

  int16_t int16_max = t;
  float flt_max = f;

  printf("\nINT16_MIN = %d\n", INT16_MIN);

  for (int16_t i = 0; i > INT16_MIN; i++){
    f = t = INT16_MIN + i;
    if (f == INT16_MIN) {
      printf("\nFAILURE\n");
      printf("\nValue (float) = %f", (double)f);
      printf("\nReal Value (int16_t) = %d", t);
      printf("\nConverted Value (int16_t) = %d\n", (int16_t)f);
    } else {
      printf("\nSUCCESS\n");
      printf("\nValue (float) = %f", (double)f);
      printf("\nReal Value (int16_t) = %d", t);
      printf("\nConverted Value (int16_t) = %d\n", (int16_t)f);
      break;
    }
  }

  int16_t int16_min = t;
  float flt_min = f;

  printf("\n\nFinal Results - INT16 to FLOAT\n\n");

  printf("********************************************");
  printf("\nINT16_MAX = %d", INT16_MAX);
  printf("\nMaximum FLOAT = %f", (double)flt_max);
  printf("\nMaximum INT16 = %d\n", int16_max);
  printf("********************************************");

  printf("\n\n");

  printf("********************************************");
  printf("\nINT16_MIN = %d", INT16_MIN);
  printf("\nMinimum FLOAT = %f", (double)flt_min);
  printf("\nMinimum INT16 = %d\n", int16_min);
  printf("********************************************");

  printf("\n\n");

  // **************************************************************************************

  return 0;
}
