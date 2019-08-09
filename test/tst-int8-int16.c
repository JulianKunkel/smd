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
  // check the range
  if(ov < SHRT_MIN || ov > SHRT_MAX){
    return 1;
  }
  *p1 = (int16_t) ov;

  int16_t p2 = (int16_t) i8;

  int16_t p3 = *(int16_t *)&i8;

  printf("\n\ni8 = %d", i8);

  printf("\n\np1 = %d", *p1);

  printf("\n\np2 = %d", p2);

  printf("\n\np3 = %d", p3);

  printf("\n\n");

  return 0;
}
