#include <assert.h>
#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {

  printf("\n\nTesting DOUBLE to INT64!\n");

  double d = INT64_MAX, val;
  double ov;

  printf("\nINT64_MAX = %ld\n\n", INT64_MAX);

  for (int64_t i = 0; i < INT64_MAX; i++){
    val = d - i;
    ov = (double) val;
    // check the range
    if (ov == INT64_MAX) {
      printf("FAILURE ");
    } else {
      printf("\n\nSUCCESS\n");
      printf("\nValue = %lf\n", val);
      break;
    }
  }

  d = INT64_MIN;

  printf("\n\n\nINT64_MIN = %ld\n\n", INT64_MIN);

  for (int64_t i = 0; i > INT64_MIN; i++){
    val = d + i;
    ov = (double) val;
    // check the range
    if (ov == INT64_MIN) {
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
