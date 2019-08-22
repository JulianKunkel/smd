#include <assert.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {

  printf("\n\nTesting UINT64 to DOUBLE!\n");

  uint64_t t;
  double f;

  printf("\nUINT64_MAX = %lu\n\n", UINT64_MAX);

  for (uint64_t i = 0; i < UINT64_MAX; i++){
    f = t = UINT64_MAX - i;
    if (f == UINT64_MAX) {
      // printf("\nFAILURE ");
      // printf("\nValue (double) = %lf", f);
      // printf("\nValue (uint64_t) = %lu\n", t);
    } else {
      printf("\nSUCCESS");
      printf("\nValue = %lf", f);
      printf("\nValue = %lu\n", t);
      break;
    }
  }

  uint64_t uint64_max = t;
  double dbl_max = f;

  printf("\n\nFinal Results - UINT64 to DOUBLE\n\n");

  printf("********************************************");
  printf("\nUINT64_MAX = %lu", UINT64_MAX);
  printf("\nMaximum DOUBLE = %lf", dbl_max);
  printf("\nMaximum UINT64 = %lu\n", uint64_max);
  printf("********************************************");

  printf("\n\n");

  // **************************************************************************************

  return 0;
}
