#include <assert.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {

  printf("\n\nTesting UINT16 to FLOAT!\n");

  uint16_t t;
  float f;

  printf("\nUINT16_MAX = %u\n", UINT16_MAX);

  for (uint16_t i = 0; i < UINT16_MAX; i++){
    f = t = UINT16_MAX - i;
    if (f == UINT16_MAX) {
      printf("\nFAILURE\n");
      printf("\nValue (float) = %f", (double)f);
      printf("\nReal Value (uint16_t) = %u", t);
      printf("\nConverted Value (uint16_t) = %u\n", (uint16_t)f);
    } else {
      printf("\nSUCCESS\n");
      printf("\nValue (float) = %f", (double)f);
      printf("\nReal Value (uint16_t) = %u", t);
      printf("\nConverted Value (uint16_t) = %u\n", (uint16_t)f);
      break;
    }
  }

  uint16_t uint16_max = t;
  float flt_max = f;

  printf("\n\nFinal Results - UINT16 to FLOAT\n\n");

  printf("********************************************");
  printf("\nUINT16_MAX = %u", UINT16_MAX);
  printf("\nMaximum FLOAT = %f", (double)flt_max);
  printf("\nMaximum UINT16 = %u\n", uint16_max);
  printf("********************************************");

  printf("\n\n");

  // **************************************************************************************

  return 0;
}
