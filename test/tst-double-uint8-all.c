#include <assert.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {

  printf("\n\nTesting UINT8 to DOUBLE!\n");

  uint8_t t;
  double d;

  printf("\nUINT8_MAX = %u\n", UINT8_MAX);

  for (uint8_t i = 0; i < UINT8_MAX; i++){
    d = t = UINT8_MAX - i;
    if (d == UINT8_MAX) {
      printf("\nFAILURE\n");
      printf("\nValue (double) = %lf", d);
      printf("\nReal Value (uint8_t) = %u", t);
      printf("\nConverted Value (uint8_t) = %u", (uint8_t)d);
    } else {
      printf("\n\nSUCCESS\n");
      printf("\nValue (double) = %lf", d);
      printf("\nReal Value (uint8_t) = %u", t);
      printf("\nConverted Value (uint8_t) = %u", (uint8_t)d);
      break;
    }
  }

  uint8_t uint8_max = t;
  double dbl_max = d;

  printf("\n\n\nFinal Results - UINT8 to DOUBLE\n\n");

  printf("********************************************");
  printf("\nUINT8_MAX = %u", UINT8_MAX);
  printf("\nMaximum DOUBLE = %lf", dbl_max);
  printf("\nMaximum UINT8 = %u\n", uint8_max);
  printf("********************************************");

  printf("\n\n");

  // **************************************************************************************

  return 0;
}
