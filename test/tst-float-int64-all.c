#include <assert.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {

  printf("\n\nTesting FLOAT to INT64!\n");

  float f = INT64_MAX, val;
  float ov;

  printf("\nINT64_MAX = %ld\n\n", INT64_MAX);

  for (int64_t i = 0; i < INT64_MAX; i+=100000000000){
    val = f - i;
    ov = (float) val;
    // check the range
    if (ov == INT64_MAX) {
      printf("FAILURE ");
      printf("\nValue = %f\n", (double)val);
      printf("\nValue = %ld\n", i);
    } else {
      printf("\n\nSUCCESS\n");
      printf("\nValue = %f\n", (double)val);
      break;
    }
  }

  for (int64_t i = 0; i < INT64_MAX; i+=100){
    val = f - i;
    ov = (float) val;
    // check the range
    if (ov == INT64_MAX) {
    } else {
      printf("\n\nSUCCESS\n");
      printf("\nValue = %f\n", (double)val);
      break;
    }
  }

  f = INT64_MIN;

  printf("\n\n\nINT64_MIN = %ld\n\n", INT64_MIN);

  for (int64_t i = 0; i > INT64_MIN; i+=100000000000){
    val = f + i;
    ov = (float) val;
    // check the range
    if (ov == INT64_MIN) {
      printf("FAILURE ");
      printf("\nValue = %f\n", (double)val);
      printf("\nValue = %ld\n", i);
    } else {
      printf("\n\nSUCCESS\n");
      printf("\nValue = %f\n", (double)val);
      break;
    }
  }

  for (int64_t i = 0; i > INT64_MIN; i+=10000){
    val = f + i;
    ov = (float) val;
    // check the range
    if (ov == INT64_MIN) {
    } else {
      printf("\n\nSUCCESS\n");
      printf("\nValue = %f\n", (double)val);
      break;
    }
  }

  printf("\n\n");

  // **************************************************************************************

  return 0;
}
