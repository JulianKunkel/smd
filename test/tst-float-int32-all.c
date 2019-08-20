#include <assert.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {

  printf("\n\nTesting FLOAT to INT32!\n");

  float f = INT32_MAX, val;
  float ov;

  printf("\nINT32_MAX = %d\n\n", INT32_MAX);

  for (int i = 0; i < INT32_MAX; i++){
    val = f - i;
    ov = (float) val;
    // check the range
    if (ov == INT32_MAX) {
      printf("FAILURE ");
    } else {
      printf("\n\nSUCCESS\n");
      printf("\nValue = %f\n", (double)val);
      break;
    }
  }

  f = INT32_MIN;

  printf("\nINT32_MIN = %d\n\n", INT32_MIN);

  for (int i = 0; i > INT32_MIN; i++){
    val = f + i;
    ov = (float) val;
    // check the range
    if (ov == INT32_MIN) {
      printf("FAILURE ");
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
