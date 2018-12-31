#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <smd-internal.h>


/**
 * Primitive datatypes
 */

static smd_dtype_t SMD_DTYPE_UNKNOWN_d = {.type = SMD_TYPE_UNKNOWN};
smd_dtype_t * SMD_DTYPE_UNKNOWN = & SMD_DTYPE_UNKNOWN_d;

static smd_dtype_t SMD_DTYPE_INT8_d = {.type = SMD_TYPE_INT8};
smd_dtype_t * SMD_DTYPE_INT8 = & SMD_DTYPE_INT8_d;

static smd_dtype_t SMD_DTYPE_INT16_d = {.type = SMD_TYPE_INT16};
smd_dtype_t * SMD_DTYPE_INT16 = & SMD_DTYPE_INT16_d;

static smd_dtype_t SMD_DTYPE_INT32_d = {.type = SMD_TYPE_INT32};
smd_dtype_t * SMD_DTYPE_INT32 = & SMD_DTYPE_INT32_d;

static smd_dtype_t SMD_DTYPE_INT64_d = {.type = SMD_TYPE_INT64};
smd_dtype_t * SMD_DTYPE_INT64 = & SMD_DTYPE_INT64_d;

static smd_dtype_t SMD_DTYPE_UINT8_d = {.type = SMD_TYPE_UINT8};
smd_dtype_t * SMD_DTYPE_UINT8 = & SMD_DTYPE_UINT8_d;

static smd_dtype_t SMD_DTYPE_UINT16_d = {.type = SMD_TYPE_UINT16};
smd_dtype_t * SMD_DTYPE_UINT16 = & SMD_DTYPE_UINT16_d;

static smd_dtype_t SMD_DTYPE_UINT32_d = {.type = SMD_TYPE_UINT32};
smd_dtype_t * SMD_DTYPE_UINT32 = & SMD_DTYPE_UINT32_d;

static smd_dtype_t SMD_DTYPE_UINT64_d = {.type = SMD_TYPE_UINT64};
smd_dtype_t * SMD_DTYPE_UINT64 = & SMD_DTYPE_UINT64_d;

static smd_dtype_t SMD_DTYPE_FLOAT_d = {.type = SMD_TYPE_FLOAT};
smd_dtype_t * SMD_DTYPE_FLOAT = & SMD_DTYPE_FLOAT_d;

static smd_dtype_t SMD_DTYPE_DOUBLE_d = {.type = SMD_TYPE_DOUBLE};
smd_dtype_t * SMD_DTYPE_DOUBLE = & SMD_DTYPE_DOUBLE_d;

static smd_dtype_t SMD_DTYPE_CHAR_d = {.type = SMD_TYPE_CHAR};
smd_dtype_t * SMD_DTYPE_CHAR = & SMD_DTYPE_CHAR_d;

static smd_dtype_t SMD_DTYPE_STRING_d = {.type = SMD_TYPE_STRING};
smd_dtype_t * SMD_DTYPE_STRING = & SMD_DTYPE_STRING_d;
