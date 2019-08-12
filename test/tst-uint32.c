#include <limits.h>
#include <stdio.h>

#include <smd.h>

void convert(void *in, void *out) {
  int64_t *p = (int64_t *)out;
  int32_t ov = *(int32_t *)in;
  *p = (int64_t)ov;
}

int main() {
  // From uint32 to int8

  uint32_t ui32 = 120;

  printf("\n\nui32 = %d", ui32);
  printf("\n\nSCHAR_MIN = %d\nSCHAR_MAX = %d", SCHAR_MIN, SCHAR_MAX);

  if (ui32 > SCHAR_MAX) {
    printf("\n\nConversion not possible: ui32 = %d > SCHAR_MAX = %d\n\n", ui32, SCHAR_MAX);
  }

  if (ui32 < SCHAR_MIN) {
    printf("\n\nConversion not possible: ui32 = %d < SCHAR_MIN = %d\n\n", ui32, SCHAR_MIN);
  }

  printf("\n\nWell, let's just ignore and make the conversion anyway!");

  int8_t p = (int8_t)ui32;
  printf("\n\np = %d\n\n", p);
  printf("Conversion OK. Great!\n\n");

  // From int32 to int64

  int32_t i32 = -20000000;

  printf("\n\ni32 = %d", i32);

  printf("\n\nWell, let's just ignore and make the conversion anyway!");

  int64_t q = (int64_t)i32;
  printf("\n\nw = %ld", q);
  printf("\n\nConversion OK. Great!\n\n");

  printf("\n\nNow, let's try the conversion using a function!");

  int32_t r = -20000000;
  int64_t s;

  convert((void *)&r, (int64_t *)&s);

  printf("\n\nr = %d", r);
  printf("\n\ns = %ld", s);
  printf("\n\nConversion OK. Great!\n\n");

  return 0;
}
