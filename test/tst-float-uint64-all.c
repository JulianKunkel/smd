#include <assert.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {

  printf("\n\nTesting UINT64 to FLOAT!\n");

  uint64_t t;
  float f;

  printf("\nUINT64_MAX = %lu\n", UINT64_MAX);

  printf("\nFAILURE\n");

  // for (uint64_t i = 0; i < UINT64_MAX; i++){
  for (uint64_t i = 0; i < UINT64_MAX; i+=10000){
    f = t = UINT64_MAX - i;
    if (f == UINT64_MAX) {
      // printf("\nFAILURE");
      // printf("\nValue = %f", (double)f);
      // printf("\nReal Value (uint64_t) = %lu", t);
      // printf("\nConverted Value (uint64_t) = %lu", (uint64_t)f);
    } else {
      printf("\nSUCCESS\n");
      printf("\nValue = %f", (double)f);
      printf("\nReal Value (uint64_t) = %lu", t);
      printf("\nConverted Value (uint64_t) = %lu", (uint64_t)f);
      break;
    }
  }

  uint64_t uint64_max = t;
  float flt_max = f;

  printf("\n\n\nFinal Results - UINT64 to FLOAT\n\n");

  printf("********************************************");
  printf("\nUINT64_MAX = %lu", UINT64_MAX);
  printf("\nMaximum FLOAT = %f", (double)flt_max);
  printf("\nMaximum UINT64 = %lu\n", uint64_max);
  printf("********************************************");

  printf("\n\n");

  // **************************************************************************************

  return 0;
}
