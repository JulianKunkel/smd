#include <assert.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {

  printf("\n\nTesting DOUBLE to INT32!\n");

  double d = INT32_MAX, val;
  double ov;

  printf("\nINT32_MAX = %d\n\n", INT32_MAX);

  for (int32_t i = 0; i < INT32_MAX; i++){
    val = d - i;
    ov = (double) val;
    // check the range
    if (ov == INT32_MAX) {
      printf("FAILURE ");
    } else {
      printf("\n\nSUCCESS\n");
      printf("\nValue = %lf\n", val);
      break;
    }
  }

  d = INT32_MIN;

  printf("\n\n\nINT32_MIN = %d\n\n", INT32_MIN);

  for (int32_t i = 0; i > INT32_MIN; i++){
    val = d + i;
    ov = (double) val;
    // check the range
    if (ov == INT32_MIN) {
      printf("FAILURE ");
    } else {
      printf("\n\nSUCCESS\n");
      printf("\nValue = %lf\n", val);
      break;
    }
  }

  printf("\n\n");

  // **************************************************************************************

  return 0;
}
