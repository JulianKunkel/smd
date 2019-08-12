#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <smd.h>

int main() {
  printf("\n\nTesting UINT64!\n");

  uint64_t ui64_1 = 9000000000000000000; // Changes to 9000000202358128640!
  // uint64_t ui64_2 = 18446744073709551610; // It doesn't work! No clue!
  uint64_t ui64_3 = LONG_MAX;
  uint64_t ui64_4 = ULONG_MAX;

  printf("\n\n%ld\n", ui64_1);
  // printf("\n\n%ld\n", ui64_2);
  printf("\n\n%ld\n", ui64_3);
  printf("\n\n%ld\n", ui64_4);

  printf("\n\n%ld\n", LONG_MAX);
  printf("\n\n%ld\n", ULONG_MAX);

  // https://www.tutorialspoint.com/c_standard_library/limits_h

  // ULONG_MAX	18446744073709551615	Defines the maximum value for an unsigned long int.

  // **************************************************************************************

  return 0;
}
