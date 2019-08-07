#include <stdio.h>
#include <limits.h>

#include <smd.h>

int main() {

  // From uint32 to int8

  uint32_t ui32 = 120;

  printf("\n\nui32 = %d", ui32);
  printf("\n\nSCHAR_MIN = %d\nSCHAR_MAX = %d", SCHAR_MIN, SCHAR_MAX);

  if(ui32 > SCHAR_MAX){
    printf("\n\nConversion not possible: ui32 = %d > SCHAR_MAX = %d", ui32, SCHAR_MAX);
  }

  if(ui32 < SCHAR_MIN){
    printf("\n\nConversion not possible: ui32 = %d < SCHAR_MIN = %d", ui32, SCHAR_MIN);
  }

  printf("\n\nWell, let's just ignore and make the conversion anyway!");

  int8_t p = (int8_t) ui32;
  printf("\n\np = %d\n\n", p);
  printf("Conversion OK. Great!\n\n");

  return 0;
}
