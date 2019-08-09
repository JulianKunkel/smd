#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <smd.h>

int main() {

  // From int16 to int8

  int8_t i8 = -120;
  char *out;
  out = malloc(sizeof(char));

  int16_t *p1 = (int16_t *)out;

  int8_t ov = *(int8_t*)&i8;
  *p1 = (int16_t) ov;

  printf("\n\ni8 = %d", i8);

  printf("\n\np1 = %d", *p1);

  return 0;
}
