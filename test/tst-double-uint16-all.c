#include <assert.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {

  printf("\n\nTesting UINT16 to DOUBLE!\n");

  uint16_t t;
  double d;

  printf("\nUINT16_MAX = %u\n", UINT16_MAX);

  for (uint16_t i = 0; i < UINT16_MAX; i++){
    d = t = UINT16_MAX - i;
    if (d == UINT16_MAX) {
      printf("\nFAILURE\n");
      printf("\nValue (double) = %lf", d);
      printf("\nReal Value (uint16_t) = %u", t);
      printf("\nConverted Value (uint16_t) = %u", (uint16_t)d);
    } else {
      printf("\n\nSUCCESS\n");
      printf("\nValue (double) = %lf", d);
      printf("\nReal Value (uint16_t) = %u", t);
      printf("\nConverted Value (uint16_t) = %u", (uint16_t)d);
      break;
    }
  }

  uint16_t uint16_max = t;
  double dbl_max = d;

  printf("\n\n\nFinal Results - UINT16 to DOUBLE\n\n");

  printf("********************************************");
  printf("\nUINT16_MAX = %u", UINT16_MAX);
  printf("\nMaximum DOUBLE = %lf", dbl_max);
  printf("\nMaximum UINT16 = %u\n", uint16_max);
  printf("********************************************");

  printf("\n\n");

  // **************************************************************************************

  return 0;
}
