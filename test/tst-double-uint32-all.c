#include <assert.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {

  printf("\n\nTesting UINT32 to DOUBLE!\n");

  uint32_t t;
  double f;

  printf("\nUINT32_MAX = %u\n\n", UINT32_MAX);

  for (uint32_t i = 0; i < UINT32_MAX; i++){
    f = t = UINT32_MAX - i;
    if (f == UINT32_MAX) {
      // printf("\nFAILURE ");
      // printf("\nValue (float) = %lf", f);
      // printf("\nValue (uint32_t) = %d\n", t);
    } else {
      printf("\nSUCCESS");
      printf("\nValue = %lf", f);
      printf("\nValue = %u\n", t);
      break;
    }
  }

  uint32_t uint32_max = t;
  double dbl_max = f;

  printf("\n\nFinal Results - UINT32 to DOUBLE\n\n");

  printf("********************************************");
  printf("\nUINT32_MAX = %u", UINT32_MAX);
  printf("\nMaximum DOUBLE = %lf", dbl_max);
  printf("\nMaximum UINT32 = %u\n", uint32_max);
  printf("********************************************");

  printf("\n\n");

  // **************************************************************************************

  return 0;
}
