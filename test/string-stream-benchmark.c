#define _GNU_SOURCE

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <smd.h>


#define kRepetitions 1000
const int kCharacterCount = 100000;
const int kAllocSize = 100; //for the snprintf() test

static struct timespec curTime() {
  struct timespec result;
  clock_gettime(CLOCK_MONOTONIC, &result);
  return result;
}

static double elapsedSeconds(struct timespec startTime, struct timespec endTime) {
  return endTime.tv_sec - startTime.tv_sec + ((double)endTime.tv_nsec - (double)startTime.tv_nsec)/(1000*1000*1000);
}

int main() {
  fprintf(stderr, "catenating many strings\n");
  {
    fprintf(stderr, "\tstrcat(): ");
    struct timespec t0 = curTime();
    char* result = malloc(kCharacterCount + 1);
    *result = 0;  //make it a valid empty string
    for(int i = 0; i < kCharacterCount; i++) {
      strcat(result, "c");
    }
    struct timespec t1 = curTime();
    fprintf(stderr, "%fs\n", elapsedSeconds(t0, t1));
    assert(strlen(result) == kCharacterCount);
    free(result);
  }
  {
    fprintf(stderr, "\tasprintf(): ");
    struct timespec t0 = curTime();
    char* result = strdup("");
    for(int i = 0; i < kCharacterCount; i++) {
      char* copy;
      asprintf(&copy, "%sc", result);
      free(result);
      result = copy;
    }
    struct timespec t1 = curTime();
    fprintf(stderr, "%fs\n", elapsedSeconds(t0, t1));
    assert(strlen(result) == kCharacterCount);
    free(result);
  }
  {
    fprintf(stderr, "\tsmd_string_stream_t: ");
    struct timespec t0 = curTime();
    smd_string_stream_t* stream = smd_string_stream_create();
    for(int i = 0; i < kCharacterCount; i++) {
      smd_string_stream_printf(stream, "c");
    }
    char* result = smd_string_stream_close(stream, NULL);
    struct timespec t1 = curTime();
    fprintf(stderr, "%fs\n", elapsedSeconds(t0, t1));
    assert(strlen(result) == kCharacterCount);
    free(result);
  }

  fprintf(stderr, "\nconcatenating two long strings\n");
  char* input1 = malloc(kCharacterCount + 1);
  for(int i = 0; i < kCharacterCount; i++) input1[i] = 'A' + i%26;
  input1[kCharacterCount] = 0;
  char* input2 = strdup(input1);
  {
    fprintf(stderr, "\tstrcat(): ");
    char* result = NULL;
    struct timespec t0 = curTime();
    for(int i = 0; i < kRepetitions; i++) {
      if(result) free(result);
      result = malloc(2*kCharacterCount + 1);
      *result = 0;  //make it a valid empty string
      strcat(result, input1);
      strcat(result, input2);
    }
    struct timespec t1 = curTime();
    fprintf(stderr, "%fs\n", elapsedSeconds(t0, t1));
    assert(strlen(result) == 2*kCharacterCount);
    free(result);
  }
  {
    fprintf(stderr, "\tstrcat() + strlen(): ");
    char* result = NULL;
    struct timespec t0 = curTime();
    for(int i = 0; i < kRepetitions; i++) {
      if(result) free(result);
      int length = strlen(input1) + strlen(input2);
      result = malloc(length + 1);
      *result = 0;  //make it a valid empty string
      strcat(result, input1);
      strcat(result, input2);
    }
    struct timespec t1 = curTime();
    fprintf(stderr, "%fs\n", elapsedSeconds(t0, t1));
    assert(strlen(result) == 2*kCharacterCount);
    free(result);
  }
  {
    fprintf(stderr, "\tasprintf(): ");
    char* result = NULL;
    struct timespec t0 = curTime();
    for(int i = 0; i < kRepetitions; i++) {
      if(result) free(result);
      asprintf(&result, "%s%s", input1, input2);
    }
    struct timespec t1 = curTime();
    fprintf(stderr, "%fs\n", elapsedSeconds(t0, t1));
    assert(strlen(result) == 2*kCharacterCount);
    free(result);
  }
  {
    fprintf(stderr, "\tsmd_string_stream_t: ");
    char* result = NULL;
    struct timespec t0 = curTime();
    for(int i = 0; i < kRepetitions; i++) {
      if(result) free(result);
      smd_string_stream_t* stream = smd_string_stream_create();
      smd_string_stream_printf(stream, "%s%s", input1, input2);
      result = smd_string_stream_close(stream, NULL);
    }
    struct timespec t1 = curTime();
    fprintf(stderr, "%fs\n", elapsedSeconds(t0, t1));
    assert(strlen(result) == 2*kCharacterCount);
    free(result);
  }

  fprintf(stderr, "\nformatting many short strings\n");
  {
    fprintf(stderr, "\tsnprintf(): ");
    struct timespec t0 = curTime();
    char* strings[kRepetitions];
    for(int i = 0; i < kRepetitions; i++) strings[i] = malloc(kAllocSize);
    for(int i = 0; i < kRepetitions; i++) {
      snprintf(strings[i], kAllocSize, "foo(\"%s\"): %d\n", "Hello World!", i);
    }
    for(int i = 0; i < kRepetitions; i++) free(strings[i]);
    struct timespec t1 = curTime();
    fprintf(stderr, "%fs\n", elapsedSeconds(t0, t1));
  }
  {
    fprintf(stderr, "\tasprintf(): ");
    char* strings[kRepetitions];
    struct timespec t0 = curTime();
    for(int i = 0; i < kRepetitions; i++) {
      asprintf(&strings[i], "foo(\"%s\"): %d\n", "Hello World!", i);
    }
    for(int i = 0; i < kRepetitions; i++) free(strings[i]);
    struct timespec t1 = curTime();
    fprintf(stderr, "%fs\n", elapsedSeconds(t0, t1));
  }{
    fprintf(stderr, "\tsmd_string_stream_t: ");
    char* strings[kRepetitions];
    struct timespec t0 = curTime();
    for(int i = 0; i < kRepetitions; i++) {
      smd_string_stream_t* stream = smd_string_stream_create();
      smd_string_stream_printf(stream, "foo(\"%s\"): %d\n", "Hello World!", i);
      strings[i] = smd_string_stream_close(stream, NULL);
    }
    for(int i = 0; i < kRepetitions; i++) free(strings[i]);
    struct timespec t1 = curTime();
    fprintf(stderr, "%fs\n", elapsedSeconds(t0, t1));
  }

  printf("\nOK\n");
}
