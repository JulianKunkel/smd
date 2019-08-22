#include <assert.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {

  printf("\n\nTesting INT32 to FLOAT!\n");

  int32_t t;
  float f;

  printf("\nINT32_MAX = %d\n\n", INT32_MAX);

  for (int32_t i = 0; i < INT32_MAX; i++){
    f = t = INT32_MAX - i;
    if (f == INT32_MAX) {
      printf("\nFAILURE ");
      printf("\nValue (float) = %f", (double)f);
      printf("\nValue (int32_t) = %d\n", t);
    } else {
      printf("\nSUCCESS");
      printf("\nValue = %f", (double)f);
      printf("\nValue = %d\n", t);
      break;
    }
  }

  int32_t int32_max = t;
  float flt_max = f;

  printf("\n\n\nINT32_MIN = %d\n\n", INT32_MIN);

  for (int32_t i = 0; i > INT32_MIN; i++){
    f = t = INT32_MIN + i;
    if (f == INT32_MIN) {
      printf("\nFAILURE ");
      printf("\nValue (float) = %f", (double)f);
      printf("\nValue (int32_t) = %d\n", t);
    } else {
      printf("\nSUCCESS");
      printf("\nValue = %f", (double)f);
      printf("\nValue = %d\n", t);
      break;
    }
  }

  int32_t int32_min = t;
  float flt_min = f;

  printf("\n\nFinal Results - INT32 to FLOAT\n\n");

  printf("********************************************");
  printf("\nINT32_MAX = %d", INT32_MAX);
  printf("\nMaximum FLOAT = %f", (double)flt_max);
  printf("\nMaximum INT32 = %d\n", int32_max);
  printf("********************************************");

  printf("\n\n");

  printf("********************************************");
  printf("\nINT32_MIN = %d", INT32_MIN);
  printf("\nMinimum FLOAT = %f", (double)flt_min);
  printf("\nMinimum INT32 = %d\n", int32_min);
  printf("********************************************");

  printf("\n\n");

  // **************************************************************************************

  return 0;
}
