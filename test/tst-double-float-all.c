#include <assert.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {

  printf("\n\nTesting FLOAT to DOUBLE!\n");

  float f;
  double d;

  printf("\nFLOAT_MAX = %f\n\n", (double)FLT_MAX);

  printf("\nFAILURE\n");

  for (int64_t i = 0; i < FLT_MAX; i++){
    d = f = FLT_MAX - i;
    if (d == (double)FLT_MAX) {
      // printf("\nFAILURE");
      // printf("\nValue (double) = %lf", d);
      // printf("\nReal Value (float) = %ld", t);
      // printf("\nConverted Value (float) = %f", (double)f);
      printf("\nConverted Value (float) = %ld", i);
    } else {
      printf("\n\nSUCCESS\n");
      printf("\nValue (double) = %lf", d);
      printf("\nReal Value (float) = %f", (double)f);
      printf("\nConverted Value (float) = %f", (double)(float)d);
      break;
    }
  }

  float float_max = f;
  double dbl_max = d;

  printf("\n\n\nFLT_MIN = %f\n\n", (double)FLT_MIN);

  printf("\nFAILURE\n");

  for (int64_t i = 0; i > FLT_MIN; i++){
    d = f = FLT_MIN + i;
    if (d == (double)FLT_MIN) {
      // printf("\nFAILURE");
      // printf("\nValue (double) = %lf", d);
      // printf("\nReal Value (float) = %f", f);
      // printf("\nConverted Value (float) = %f", (double)f);
    } else {
      printf("\n\nSUCCESS\n");
      printf("\nValue (double) = %lf", d);
      printf("\nReal Value (float) = %f", (double)f);
      printf("\nConverted Value (float) = %f", (double)(float)d);
      break;
    }
  }

  float float_min = f;
  double dbl_min = d;

  printf("\n\n\nFinal Results - FLOAT to DOUBLE\n\n");

  printf("********************************************");
  printf("\nFLOAT_MAX = %f", (double)FLT_MAX);
  printf("\nMaximum DOUBLE = %lf", dbl_max);
  printf("\nMaximum FLOAT = %f\n", (double)float_max);
  printf("********************************************");

  printf("\n\n");

  printf("********************************************");
  printf("\nFLOAT_MIN = %f", (double)FLT_MIN);
  printf("\nMinimum DOUBLE = %lf", dbl_min);
  printf("\nMinimum FLOAT = %f\n", (double)float_min);
  printf("********************************************");

  printf("\n\n");

  // **************************************************************************************

  return 0;
}
