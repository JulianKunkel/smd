#include <assert.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {

  printf("\n\nTesting UINT8 to FLOAT!\n");

  uint8_t t;
  float f;

  printf("\nUINT8_MAX = %u\n", UINT8_MAX);

  for (uint8_t i = 0; i < UINT8_MAX; i++){
    f = t = UINT8_MAX - i;
    if (f == UINT8_MAX) {
      printf("\nFAILURE\n");
      printf("\nValue (float) = %f", (double)f);
      printf("\nReal Value (uint8_t) = %u", t);
      printf("\nConverted Value (uint8_t) = %u\n", (uint8_t)f);
    } else {
      printf("\nSUCCESS\n");
      printf("\nValue (float) = %f", (double)f);
      printf("\nReal Value (uint8_t) = %u", t);
      printf("\nConverted Value (uint8_t) = %u\n", (uint8_t)f);
      break;
    }
  }

  uint8_t uint8_max = t;
  float flt_max = f;

  printf("\n\nFinal Results - UINT8 to FLOAT\n\n");

  printf("********************************************");
  printf("\nUINT8_MAX = %u", UINT8_MAX);
  printf("\nMaximum FLOAT = %f", (double)flt_max);
  printf("\nMaximum UINT8 = %u\n", uint8_max);
  printf("********************************************");

  printf("\n\n");

  // **************************************************************************************

  return 0;
}
