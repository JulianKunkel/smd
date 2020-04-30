#include <stdio.h>
#include <stdlib.h>

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>

#include <smd-internal.h>

#pragma GCC diagnostic ignored "-Wdouble-promotion"

#define use_type_ptr(t) (t->type < SMD_TYPE_PRIMITIVE_END || (t->type == SMD_TYPE_EXTENT && t->specifier.u.ext.base->type < SMD_TYPE_PRIMITIVE_END) || t->type == SMD_TYPE_DTYPE)

// Native Datatypes ///////////////////////////////////////////////////////////
static size_t smd_sizeof(smd_basic_type_t type) {
  switch (type) {
    case SMD_TYPE_DTYPE:
      return sizeof(void *);
    case SMD_TYPE_INT8:
      //case SMD_TYPE_CHAR_UTF8:
      return sizeof(int8_t);
    case SMD_TYPE_INT16:
      //case SMD_TYPE_CHAR_UTF16:
      return sizeof(int16_t);
    case SMD_TYPE_INT32:
      //case SMD_TYPE_CHAR_UTF32:
      return sizeof(int32_t);
    case SMD_TYPE_INT64:
      return sizeof(int64_t);
    case SMD_TYPE_UINT8:
      return sizeof(uint8_t);
    case SMD_TYPE_UINT16:
      return sizeof(uint16_t);
    case SMD_TYPE_UINT32:
      return sizeof(uint32_t);
    case SMD_TYPE_UINT64:
      return sizeof(uint64_t);
    case SMD_TYPE_FLOAT:
      return sizeof(float);
    case SMD_TYPE_DOUBLE:
      return sizeof(double);
    default:
      assert(0 && "NOT IMPLEMENTED DTYPE size");
      return 1;
  }
}

void smd_copy_value(smd_dtype_t *type, void *to, void *from) {
  assert(type);
  assert(to);
  assert(from);

  size_t cnt = smd_sizeof(type->type);
  memcpy(to, from, cnt);
}

char *smd_dup_escaped_varname(const char *name) {
  //Generate a conform variable name removing all non-printable characters
  int len = strlen(name); // max length
  char *buff = malloc(len + 1);
  int i;
  char *orig = buff;
  for (i = 0; name[i] != 0; i++) {
    char c = name[i];
    if (c < 32 || c > 127 || c == 92 || c == 34 || c == 64) {
      continue;
    }
    *buff = name[i];
    buff++;
  }
  *buff = 0;
  return orig;
}

smd_basic_type_t smd_attr_get_type(smd_attr_t *attr) {
  assert(attr);
  return attr->type->type;
}

int smd_find_position_by_name(const smd_attr_t *attr, const char *name) {
  for (unsigned int i = 0; i < attr->children; i++) {
    if (strcmp(attr->childs[i]->name, name) == 0) {
      return i;
    }
  }
  return -1;
}

smd_attr_t *smd_attr_get_child_by_name(const smd_attr_t *attr, const char *name) {
  for (unsigned int i = 0; i < attr->children; i++) {
    if (strcmp(attr->childs[i]->name, name) == 0) {
      return attr->childs[i];
    }
  }
  return NULL;
}

static void smd_attr_alloc(void **out, smd_dtype_t *dtype) {
  smd_basic_type_t type = dtype->type;
  switch (type) {
    case (SMD_TYPE_EXTENT):
    case (SMD_TYPE_STRUCT):
    case (SMD_TYPE_ARRAY): {
      *out = malloc(dtype->size);
      //printf("alloced %ld to %ld\n", dtype->size, *out);
      return;
    }
    default:
      return;
  }
}

static int smd_attr_copy_val_to_internal(char *out, smd_dtype_t *t, smd_dtype_t *usertype, const void *val) {
  smd_basic_type_t type = t->type;
  //printf("E=>I %d %lld %lld\n", type, out, val);
  switch (type) {
    case (SMD_TYPE_DTYPE): {
      assert(out);
      smd_dtype_t **p = (smd_dtype_t **)out;
      *p = (smd_dtype_t *)val;
      (*p)->refcount++;
      return 0;
    }

    case (SMD_TYPE_INT8): {
      int8_t *p = (int8_t *)out;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_INT8): {
          *p = *(int8_t *)val;
          return 0;
        }

        case (SMD_TYPE_INT16): {
          int16_t ov = *(int16_t *)val;
          // check the range
          if (ov < INT8_MIN || ov > INT8_MAX) {
            return 1;
          }
          *p = (int8_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT32): {
          int32_t ov = *(int32_t *)val;
          // check the range
          if (ov < INT8_MIN || ov > INT8_MAX) {
            return 1;
          }
          *p = (int8_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT64): {
          int64_t ov = *(int64_t *)val;
          // check the range
          if (ov < INT8_MIN || ov > INT8_MAX) {
            return 1;
          }
          *p = (int8_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT8): {
          uint8_t ov = *(uint8_t *)val;
          // check the range
          if (ov > INT8_MAX) {
            return 1;
          }
          *p = (int8_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT16): {
          uint16_t ov = *(uint16_t *)val;
          // check the range
          if (ov > INT8_MAX) {
            return 1;
          }
          *p = (int8_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT32): {
          uint32_t ov = *(uint32_t *)val;
          // check the range
          if (ov > INT8_MAX) {
            return 1;
          }
          *p = (int8_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT64): {
          uint64_t ov = *(uint64_t *)val;
          // check the range
          if (ov > INT8_MAX) {
            return 1;
          }
          *p = (int8_t)ov;
          return 0;
        }

        case (SMD_TYPE_FLOAT): {
          float ov = *(float *)val;
          // check the range
          if (ov < INT8_MIN || ov > INT8_MAX) {
            return 1;
          }
          *p = (int8_t)ov;
          return 0;
        }

        case (SMD_TYPE_DOUBLE): {
          double ov = *(double *)val;
          // check the range
          if (ov < INT8_MIN || ov > INT8_MAX) {
            return 1;
          }
          *p = (int8_t)ov;
          return 0;
        }

        case (SMD_TYPE_CHAR): {
          char ov = *(char *)val;
          *p = (int8_t)ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_INT16): {
      int16_t *p = (int16_t *)out;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_INT8): {
          int8_t ov = *(int8_t *)val;
          *p = (int16_t)ov;
          return 0;
        }

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_INT16): {
          *p = *(int16_t *)val;
          return 0;
        }

        case (SMD_TYPE_INT32): {
          int32_t ov = *(int32_t *)val;
          // check the range
          if (ov < INT16_MIN || ov > INT16_MAX) {
            return 1;
          }
          *p = (int16_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT64): {
          int64_t ov = *(int64_t *)val;
          // check the range
          if (ov < INT16_MIN || ov > INT16_MAX) {
            return 1;
          }
          *p = (int16_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT8): {
          uint8_t ov = *(uint8_t *)val;
          *p = (int16_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT16): {
          uint16_t ov = *(uint16_t *)val;
          // check the range
          if (ov > INT16_MAX) {
            return 1;
          }
          *p = (int16_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT32): {
          uint32_t ov = *(uint32_t *)val;
          // check the range
          if (ov > INT16_MAX) {
            return 1;
          }
          *p = (int16_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT64): {
          uint64_t ov = *(uint64_t *)val;
          // check the range
          if (ov > INT16_MAX) {
            return 1;
          }
          *p = (int16_t)ov;
          return 0;
        }

        case (SMD_TYPE_FLOAT): {
          float ov = *(float *)val;
          // check the range
          if (ov < INT16_MIN || ov > INT16_MAX) {
            return 1;
          }
          *p = (int16_t)ov;
          return 0;
        }

        case (SMD_TYPE_DOUBLE): {
          double ov = *(double *)val;
          // check the range
          if (ov < INT16_MIN || ov > INT16_MAX) {
            return 1;
          }
          *p = (int16_t)ov;
          return 0;
        }

        case (SMD_TYPE_CHAR): {
          char ov = *(char *)val;
          *p = (int16_t)ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_INT32): {
      int32_t *p = (int32_t *)out;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_INT8): {
          int8_t ov = *(int8_t *)val;
          *p = (int32_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT16): {
          int16_t ov = *(int16_t *)val;
          *p = (int32_t)ov;
          return 0;
        }

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_INT32): {
          *p = *(int32_t *)val;
          return 0;
        }

        case (SMD_TYPE_INT64): {
          int64_t ov = *(int64_t *)val;
          // check the range
          if (ov < INT32_MIN || ov > INT32_MAX) {
            return 1;
          }
          *p = (int32_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT8): {
          uint8_t ov = *(uint8_t *)val;
          *p = (int32_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT16): {
          uint16_t ov = *(uint16_t *)val;
          *p = (int32_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT32): {
          uint32_t ov = *(uint32_t *)val;
          // check the range
          if (ov > INT32_MAX) {
            return 1;
          }
          *p = (int32_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT64): {
          uint64_t ov = *(uint64_t *)val;
          // check the range
          if (ov > INT32_MAX) {
            return 1;
          }
          *p = (int32_t)ov;
          return 0;
        }

        case (SMD_TYPE_FLOAT): {
          float ov = *(float *) val;
          // float ov = roundf(*(float *) val);
          // check the range
          if (ov <= INT32_MIN || ov >= INT32_MAX) {
            return 1;
          }
          *p = (int32_t) ov;
          return 0;
        }

        case (SMD_TYPE_DOUBLE): {
          double ov = *(double *)val;
          // check the range
          if (ov <= INT32_MIN || ov >= INT32_MAX) {
            return 1;
          }
          *p = (int32_t)ov;
          return 0;
        }

        case (SMD_TYPE_CHAR): {
          char ov = *(char *)val;
          *p = (int32_t)ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_INT64): {
      int64_t *p = (int64_t *)out;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_INT8): {
          int8_t ov = *(int8_t *)val;
          *p = (int64_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT16): {
          int16_t ov = *(int16_t *)val;
          *p = (int64_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT32): {
          int32_t ov = *(int32_t *)val;
          *p = (int64_t)ov;
          return 0;
        }

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_INT64): {
          *p = *(int64_t *)val;
          return 0;
        }

        case (SMD_TYPE_UINT8): {
          uint8_t ov = *(uint8_t *)val;
          *p = (int64_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT16): {
          uint16_t ov = *(uint16_t *)val;
          *p = (int64_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT32): {
          uint32_t ov = *(uint32_t *)val;
          *p = (int64_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT64): {
          uint64_t ov = *(uint64_t *)val;
          // check the range
          if (ov > INT64_MAX) {

            return 1;
          }
          *p = (int64_t)ov;
          return 0;
        }

        case (SMD_TYPE_FLOAT): {
          float ov = *(float *)val;
          // check the range
          if (ov <= INT64_MIN || ov >= INT64_MAX) {
            return 1;
          }
          *p = (int64_t)ov;
          return 0;
        }

        case (SMD_TYPE_DOUBLE): {
          double ov = *(double *)val;
          // check the range
          if (ov <= INT64_MIN || ov >= INT64_MAX) {
            return 1;
          }
          *p = (int64_t)ov;
          return 0;
        }

        case (SMD_TYPE_CHAR): {
          char ov = *(char *)val;
          *p = (int64_t)ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_UINT8): {
      uint8_t *p = (uint8_t *)out;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_INT8): {
          int8_t ov = *(int8_t *)val;
          // check the range
          if (ov < 0) {
            return 1;
          }
          *p = (uint8_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT16): {
          int16_t ov = *(int16_t *)val;
          // check the range
          if (ov < 0 || ov > UINT8_MAX) {
            return 1;
          }
          *p = (uint8_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT32): {
          int32_t ov = *(int32_t *)val;
          // check the range
          if (ov < 0 || ov > UINT8_MAX) {
            return 1;
          }
          *p = (uint8_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT64): {
          int64_t ov = *(int64_t *)val;
          // check the range
          if (ov < 0 || ov > UINT8_MAX) {
            return 1;
          }
          *p = (uint8_t)ov;
          return 0;
        }

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_UINT8): {
          *p = *(uint8_t *)val;
          return 0;
        }

        case (SMD_TYPE_UINT16): {
          uint16_t ov = *(uint16_t *)val;
          // check the range
          if (ov > UINT8_MAX) {
            return 1;
          }
          *p = (uint8_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT32): {
          uint32_t ov = *(uint32_t *)val;
          // check the range
          if (ov > UINT8_MAX) {
            return 1;
          }
          *p = (uint8_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT64): {
          uint64_t ov = *(uint64_t *)val;
          // check the range
          if (ov > UINT8_MAX) {
            return 1;
          }
          *p = (uint8_t)ov;
          return 0;
        }

        case (SMD_TYPE_FLOAT): {
          float ov = *(float *)val;
          // check the range
          if (ov < 0 || ov > UINT8_MAX) {
            return 1;
          }
          *p = (uint8_t)ov;
          return 0;
        }

        case (SMD_TYPE_DOUBLE): {
          double ov = *(double *)val;
          // check the range
          if (ov < 0 || ov > UINT8_MAX) {
            return 1;
          }
          *p = (uint8_t)ov;
          return 0;
        }

        case (SMD_TYPE_CHAR): {
          char ov = *(char *)val;
          // check the range
          if (ov < 0) {
            return 1;
          }
          *p = (uint8_t)ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_UINT16): {
      uint16_t *p = (uint16_t *)out;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_INT8): {
          int8_t ov = *(int8_t *)val;
          // check the range
          if (ov < 0) {
            return 1;
          }
          *p = (uint16_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT16): {
          int16_t ov = *(int16_t *)val;
          // check the range
          if (ov < 0) {
            return 1;
          }
          *p = (uint16_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT32): {
          int32_t ov = *(int32_t *)val;
          // check the range
          if (ov < 0 || ov > UINT16_MAX) {
            return 1;
          }
          *p = (uint16_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT64): {
          int64_t ov = *(int64_t *)val;
          // check the range
          if (ov < 0 || ov > UINT16_MAX) {
            return 1;
          }
          *p = (uint16_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT8): {
          uint8_t ov = *(uint8_t *)val;
          *p = (uint16_t)ov;
          return 0;
        }

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_UINT16): {
          *p = *(uint16_t *)val;
          return 0;
        }

        case (SMD_TYPE_UINT32): {
          uint32_t ov = *(uint32_t *)val;
          // check the range
          if (ov > UINT16_MAX) {
            return 1;
          }
          *p = (uint16_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT64): {
          uint64_t ov = *(uint64_t *)val;
          // check the range
          if (ov > UINT16_MAX) {
            return 1;
          }
          *p = (uint16_t)ov;
          return 0;
        }

        case (SMD_TYPE_FLOAT): {
          float ov = *(float *)val;
          // check the range
          if (ov < 0 || ov > UINT16_MAX) {
            return 1;
          }
          *p = (uint16_t)ov;
          return 0;
        }

        case (SMD_TYPE_DOUBLE): {
          double ov = *(double *)val;
          // check the range
          if (ov < 0 || ov > UINT16_MAX) {
            return 1;
          }
          *p = (uint16_t)ov;
          return 0;
        }

        case (SMD_TYPE_CHAR): {
          char ov = *(char *)val;
          // check the range
          if (ov < 0) {
            return 1;
          }
          *p = (uint16_t)ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_UINT32): {
      uint32_t *p = (uint32_t *)out;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_INT8): {
          int8_t ov = *(int8_t *)val;
          // check the range
          if (ov < 0) {
            return 1;
          }
          *p = (uint32_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT16): {
          int16_t ov = *(int16_t *)val;
          // check the range
          if (ov < 0) {
            return 1;
          }
          *p = (uint32_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT32): {
          int32_t ov = *(int32_t *)val;
          // check the range
          if (ov < 0) {
            return 1;
          }
          *p = (uint32_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT64): {
          int64_t ov = *(int64_t *)val;
          // check the range
          if (ov < 0 || ov > UINT32_MAX) {
            return 1;
          }
          *p = (uint32_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT8): {
          uint8_t ov = *(uint8_t *)val;
          *p = (uint32_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT16): {
          uint16_t ov = *(uint16_t *)val;
          *p = (uint32_t)ov;
          return 0;
        }

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_UINT32): {
          *p = *(uint32_t *)val;
          return 0;
        }

        case (SMD_TYPE_UINT64): {
          uint64_t ov = *(uint64_t *)val;
          // check the range
          if (ov > UINT32_MAX) {
            return 1;
          }
          *p = (uint32_t)ov;
          return 0;
        }

        case (SMD_TYPE_FLOAT): {
          float ov = *(float *)val;
          // check the range
          if (ov < 0 || ov >= UINT32_MAX) {
            return 1;
          }
          *p = (uint32_t)ov;
          return 0;
        }

        case (SMD_TYPE_DOUBLE): {
          double ov = *(double *)val;
          // check the range
          if (ov < 0 || ov >= UINT32_MAX) {
            return 1;
          }
          *p = (uint32_t)ov;
          return 0;
        }

        case (SMD_TYPE_CHAR): {
          char ov = *(char *)val;
          // check the range
          if (ov < 0) {
            return 1;
          }
          *p = (uint32_t)ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_UINT64): {
      uint64_t *p = (uint64_t *)out;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_INT8): {
          int8_t ov = *(int8_t *)val;
          // check the range
          if (ov < 0) {
            return 1;
          }
          *p = (uint64_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT16): {
          int16_t ov = *(int16_t *)val;
          // check the range
          if (ov < 0) {
            return 1;
          }
          *p = (uint64_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT32): {
          int32_t ov = *(int32_t *)val;
          // check the range
          if (ov < 0) {
            return 1;
          }
          *p = (uint64_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT64): {
          int64_t ov = *(int64_t *)val;
          // check the range
          if (ov < 0) {
            return 1;
          }
          *p = (uint64_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT8): {
          uint8_t ov = *(uint8_t *)val;
          *p = (uint64_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT16): {
          uint16_t ov = *(uint16_t *)val;
          *p = (uint64_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT32): {
          uint32_t ov = *(uint32_t *)val;
          *p = (uint64_t)ov;
          return 0;
        }

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_UINT64): {
          *p = *(uint64_t *)val;
          return 0;
        }

        case (SMD_TYPE_FLOAT): {
          float ov = *(float *)val;
          // check the range
          if (ov < 0 || ov >= UINT64_MAX) {
            return 1;
          }
          *p = (uint64_t)ov;
          return 0;
        }

        case (SMD_TYPE_DOUBLE): {
          double ov = *(double *)val;
          // check the range
          if (ov < 0 || ov >= UINT64_MAX) {
            return 1;
          }
          *p = (uint64_t)ov;
          return 0;
        }

        case (SMD_TYPE_CHAR): {
          char ov = *(char *)val;
          // check the range
          if (ov < 0) {
            return 1;
          }
          *p = (uint64_t)ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_FLOAT): {
      float *p = (float *)out;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_INT8): {
          int8_t ov = *(int8_t *)val;
          *p = (float)ov;
          return 0;
        }

        case (SMD_TYPE_INT16): {
          int16_t ov = *(int16_t *)val;
          *p = (float)ov;
          return 0;
        }

        case (SMD_TYPE_INT32): {
          int32_t ov = *(int32_t *)val;
          *p = (float)ov;
          // check if accuracy is precise enough
          if (ov != (int32_t)*p) {
            return 1;
          }
          return 0;
        }

        case (SMD_TYPE_INT64): {
          int64_t ov = *(int64_t *)val;
          *p = (float)ov;
          // check if accuracy is precise enough
          if (ov != (int64_t)*p) {
            return 1;
          }
          return 0;
        }

        case (SMD_TYPE_UINT8): {
          uint8_t ov = *(uint8_t *)val;
          *p = (float)ov;
          return 0;
        }

        case (SMD_TYPE_UINT16): {
          uint16_t ov = *(uint16_t *)val;
          *p = (float)ov;
          return 0;
        }

        case (SMD_TYPE_UINT32): {
          uint32_t ov = *(uint32_t *)val;
          *p = (float)ov;
          // check if accuracy is precise enough
          if (ov != (uint32_t)*p) {
            return 1;
          }
          return 0;
        }

        case (SMD_TYPE_UINT64): {
          uint64_t ov = *(uint64_t *)val;
          *p = (float)ov;
          // check if accuracy is precise enough
          if (ov != (uint64_t)*p) {
            return 1;
          }
          return 0;
        }

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_FLOAT): {
          *p = *(float *)val;
          return 0;
        }

        case (SMD_TYPE_DOUBLE): {
          double ov = *(double *)val;
          // check the range
          if (ov > 0 && (ov < (double)FLT_MIN || ov > (double)FLT_MAX)) {
            return 1;
          }
          if (ov < 0 && (ov > -(double)FLT_MIN || ov < -(double)FLT_MAX)) {
            return 1;
          }
          *p = (float)ov;
          return 0;
        }

        case (SMD_TYPE_CHAR): {
          char ov = *(char *)val;
          *p = (float)ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_DOUBLE): {
      double *p = (double *)out;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_INT8): {
          int8_t ov = *(int8_t *)val;
          *p = (double)ov;
          return 0;
        }

        case (SMD_TYPE_INT16): {
          int16_t ov = *(int16_t *)val;
          *p = (double)ov;
          return 0;
        }

        case (SMD_TYPE_INT32): {
          int32_t ov = *(int32_t *)val;
          *p = (double)ov;
          return 0;
        }

        case (SMD_TYPE_INT64): {
          int64_t ov = *(int64_t *)val;
          *p = (double)ov;
          // check if accuracy is precise enough
          if (ov != (int64_t)*p) {
            return 1;
          }
          return 0;
        }

        case (SMD_TYPE_UINT8): {
          uint8_t ov = *(uint8_t *)val;
          *p = (double)ov;
          return 0;
        }

        case (SMD_TYPE_UINT16): {
          uint16_t ov = *(uint16_t *)val;
          *p = (double)ov;
          return 0;
        }

        case (SMD_TYPE_UINT32): {
          uint32_t ov = *(uint32_t *)val;
          *p = (double)ov;
          return 0;
        }

        case (SMD_TYPE_UINT64): {
          uint64_t ov = *(uint64_t *)val;
          *p = (double)ov;
          // check if accuracy is precise enough
          if (ov != (uint64_t)*p) {
            return 1;
          }
          return 0;
        }

        case (SMD_TYPE_FLOAT): {
          float ov = *(float *)val;
          *p = (double)ov;
          return 0;
        }

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_DOUBLE): {
          *p = *(double *)val;
          return 0;
        }

        case (SMD_TYPE_CHAR): {
          char ov = *(char *)val;
          *p = (double)ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_CHAR): {
      char *p = (char *)out;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_INT8): {
          int8_t ov = *(int8_t *)val;
          *p = (char)ov;
          return 0;
        }

        case (SMD_TYPE_INT16): {
          int16_t ov = *(int16_t *)val;
          // check the range
          if (ov < SCHAR_MIN || ov > SCHAR_MAX) {
            return 1;
          }
          *p = (char)ov;
          return 0;
        }

        case (SMD_TYPE_INT32): {
          int32_t ov = *(int32_t *)val;
          // check the range
          if (ov < SCHAR_MIN || ov > SCHAR_MAX) {
            return 1;
          }
          *p = (char)ov;
          return 0;
        }

        case (SMD_TYPE_INT64): {
          int64_t ov = *(int64_t *)val;
          // check the range
          if (ov < SCHAR_MIN || ov > SCHAR_MAX) {
            return 1;
          }
          *p = (char)ov;
          return 0;
        }

        case (SMD_TYPE_UINT8): {
          uint8_t ov = *(uint8_t *)val;
          // check the range
          if (ov > SCHAR_MAX) {
            return 1;
          }
          *p = (char)ov;
          return 0;
        }

        case (SMD_TYPE_UINT16): {
          uint16_t ov = *(uint16_t *)val;
          // check the range
          if (ov > SCHAR_MAX) {
            return 1;
          }
          *p = (char)ov;
          return 0;
        }

        case (SMD_TYPE_UINT32): {
          uint32_t ov = *(uint32_t *)val;
          // check the range
          if (ov > SCHAR_MAX) {
            return 1;
          }
          *p = (char)ov;
          return 0;
        }

        case (SMD_TYPE_UINT64): {
          uint64_t ov = *(uint64_t *)val;
          // check the range
          if (ov > SCHAR_MAX) {
            return 1;
          }
          *p = (char)ov;
          return 0;
        }

        case (SMD_TYPE_FLOAT): {
          float ov = *(float *)val;
          // check the range
          if (ov < SCHAR_MIN || ov > SCHAR_MAX) {
            return 1;
          }
          *p = (char)ov;
          return 0;
        }

        case (SMD_TYPE_DOUBLE): {
          double ov = *(double *)val;
          // check the range
          if (ov < SCHAR_MIN || ov > SCHAR_MAX) {
            return 1;
          }
          *p = (char)ov;
          return 0;
        }

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_CHAR): {
          *p = *(char *)val;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_STRING): {
      char **p = (char **)out;
      *p = strdup((char *)val);
      //printf("STR %lld: %s %ld = %s\n", out, val, val, *((char**)out));
      return 0;
    }

    case (SMD_TYPE_EXTENT): {
      smd_dtype_extent_t *d = &t->specifier.u.ext;
      char *pos = (char *)val + d->lb;
      smd_attr_copy_val_to_internal(out, d->base, usertype, pos);
      return 0;
    }

    case (SMD_TYPE_STRUCT): {
      smd_dtype_struct_t *d = &t->specifier.u.str;
      char *out_pos = (char *)out;
      for (int i = 0; i < d->size; i++) {
        char *val_pos = (char *)val + d->offsets[i];
        smd_attr_copy_val_to_internal(out_pos, d->types[i], usertype, val_pos);
        out_pos += d->types[i]->size;
      }
      return 0;
    }

    case (SMD_TYPE_ARRAY): {
      smd_dtype_array_t *d = &t->specifier.u.arr;
      char *val_pos = (char *)val;
      char *out_pos = (char *)out;
      for (uint64_t i = 0; i < d->count; i++) {
        smd_attr_copy_val_to_internal(out_pos, d->base, usertype, val_pos);
        if (d->base->type == SMD_TYPE_STRING) {
          smd_attr_copy_val_to_internal(out_pos, d->base, usertype, *(char **)val_pos);
        } else {
          smd_attr_copy_val_to_internal(out_pos, d->base, usertype, val_pos);
        }
        out_pos += d->base->size;
        val_pos += d->base->extent;
      }
      return 0;
    }

    default:
      assert(0 && "SMD cannot copy unknown type");
  }
  return 0;
}

static int smd_attr_copy_val_to_external(char *out, smd_dtype_t *t, smd_dtype_t *usertype, char *val) {
  smd_basic_type_t type = t->type;
  //printf("I=>E %d %lld %lld\n", type, val, out);
  switch (type) {
    case (SMD_TYPE_INT8): {
      int8_t ov = *(int8_t *)val;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_INT8): {
          *(int8_t *)out = ov;
          return 0;
        }

        case (SMD_TYPE_INT16): {
          *(int16_t *)out = (int16_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT32): {
          *(int32_t *)out = (int32_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT64): {
          *(int64_t *)out = (int64_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT8): {
          // check the range
          if (ov < 0) {
            return 1;
          }
          *(uint8_t *)out = (uint8_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT16): {
          // check the range
          if (ov < 0) {
            return 1;
          }
          *(uint16_t *)out = (uint16_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT32): {
          // check the range
          if (ov < 0) {
            return 1;
          }
          *(uint32_t *)out = (uint32_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT64): {
          // check the range
          if (ov < 0) {
            return 1;
          }
          *(uint64_t *)out = (uint64_t)ov;
          return 0;
        }

        case (SMD_TYPE_FLOAT): {
          *(float *)out = (float)ov;
          return 0;
        }

        case (SMD_TYPE_DOUBLE): {
          *(double *)out = (double)ov;
          return 0;
        }

        case (SMD_TYPE_CHAR): {
          *(char *)out = (char)ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_INT16): {
      int16_t ov = *(int16_t *)val;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_INT8): {
          // check the range
          if (ov < INT8_MIN || ov > INT8_MAX) {
            return 1;
          }
          *(int8_t *)out = (int8_t)ov;
          return 0;
        }

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_INT16): {
          *(int16_t *)out = ov;
          return 0;
        }

        case (SMD_TYPE_INT32): {
          *(int32_t *)out = (int32_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT64): {
          *(int64_t *)out = (int64_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT8): {
          // check the range
          if (ov < 0 || ov > UINT8_MAX) {
            return 1;
          }
          *(uint8_t *)out = (uint8_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT16): {
          // check the range
          if (ov < 0) {
            return 1;
          }
          *(uint16_t *)out = (uint16_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT32): {
          // check the range
          if (ov < 0) {
            return 1;
          }
          *(uint32_t *)out = (uint32_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT64): {
          // check the range
          if (ov < 0) {
            return 1;
          }
          *(uint64_t *)out = (uint64_t)ov;
          return 0;
        }

        case (SMD_TYPE_FLOAT): {
          *(float *)out = (float)ov;
          return 0;
        }

        case (SMD_TYPE_DOUBLE): {
          *(double *)out = (double)ov;
          return 0;
        }

        case (SMD_TYPE_CHAR): {
          // check the range
          if (ov < SCHAR_MIN || ov > SCHAR_MAX) {
            return 1;
          }
          *(char *)out = (char)ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_INT32): {
      int32_t ov = *(int32_t *)val;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_INT8): {
          // check the range
          if (ov < INT8_MIN || ov > INT8_MAX) {
            return 1;
          }
          *(int8_t *)out = (int8_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT16): {
          // check the range
          if (ov < INT16_MIN || ov > INT16_MAX) {
            return 1;
          }
          *(int16_t *)out = (int16_t)ov;
          return 0;
        }

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_INT32): {
          *(int32_t *)out = ov;
          return 0;
        }

        case (SMD_TYPE_INT64): {
          *(int64_t *)out = (int64_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT8): {
          // check the range
          if (ov < 0 || ov > UINT8_MAX) {
            return 1;
          }
          *(uint8_t *)out = (uint8_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT16): {
          // check the range
          if (ov < 0 || ov > UINT16_MAX) {
            return 1;
          }
          *(uint16_t *)out = (uint16_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT32): {
          // check the range
          if (ov < 0) {
            return 1;
          }
          *(uint32_t *)out = (uint32_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT64): {
          // check the range
          if (ov < 0) {
            return 1;
          }
          *(uint64_t *)out = (uint64_t)ov;
          return 0;
        }

        case (SMD_TYPE_FLOAT): {
          *(float *)out = (float)ov;
          return 0;
        }

        case (SMD_TYPE_DOUBLE): {
          *(double *)out = (double)ov;
          return 0;
        }

        case (SMD_TYPE_CHAR): {
          // check the range
          if (ov < SCHAR_MIN || ov > SCHAR_MAX) {
            return 1;
          }
          *(char *)out = (char)ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_INT64): {
      int64_t ov = *(int64_t *)val;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_INT8): {
          // check the range
          if (ov < INT8_MIN || ov > INT8_MAX) {
            return 1;
          }
          *(int8_t *)out = (int8_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT16): {
          // check the range
          if (ov < INT16_MIN || ov > INT16_MAX) {
            return 1;
          }
          *(int16_t *)out = (int16_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT32): {
          // check the range
          if (ov < INT32_MIN || ov > INT32_MAX) {
            return 1;
          }
          *(int32_t *)out = (int32_t)ov;
          return 0;
        }

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_INT64): {
          *(int64_t *)out = ov;
          return 0;
        }

        case (SMD_TYPE_UINT8): {
          // check the range
          if (ov < 0 || ov > UINT8_MAX) {
            return 1;
          }
          *(uint8_t *)out = (uint8_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT16): {
          // check the range
          if (ov < 0 || ov > UINT16_MAX) {
            return 1;
          }
          *(uint16_t *)out = (uint16_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT32): {
          // check the range
          if (ov < 0 || ov > UINT32_MAX) {
            return 1;
          }
          *(uint32_t *)out = (uint32_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT64): {
          // check the range
          if (ov < 0) {
            return 1;
          }
          *(uint64_t *)out = (uint64_t)ov;
          return 0;
        }

        case (SMD_TYPE_FLOAT): {
          *(float *)out = (float)ov;
          return 0;
        }

        case (SMD_TYPE_DOUBLE): {
          *(double *)out = (double)ov;
          return 0;
        }

        case (SMD_TYPE_CHAR): {
          // check the range
          if (ov < SCHAR_MIN || ov > SCHAR_MAX) {
            return 1;
          }
          *(char *)out = (char)ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_UINT8): {
      uint8_t ov = *(uint8_t *)val;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_INT8): {
          // check the range
          if (ov > INT8_MAX) {
            return 1;
          }
          *(int8_t *)out = (int8_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT16): {
          *(int16_t *)out = (int16_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT32): {
          *(int32_t *)out = (int32_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT64): {
          *(int64_t *)out = (int64_t)ov;
          return 0;
        }

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_UINT8): {
          *(uint8_t *)out = ov;
          return 0;
        }

        case (SMD_TYPE_UINT16): {
          *(uint16_t *)out = (uint16_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT32): {
          *(uint32_t *)out = (uint32_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT64): {
          *(uint64_t *)out = (uint64_t)ov;
          return 0;
        }

        case (SMD_TYPE_FLOAT): {
          *(float *)out = (float)ov;
          return 0;
        }

        case (SMD_TYPE_DOUBLE): {
          *(double *)out = (double)ov;
          return 0;
        }

        case (SMD_TYPE_CHAR): {
          // check the range
          if (ov < SCHAR_MIN || ov > SCHAR_MAX) {
            return 1;
          }
          *(char *)out = (char)ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_UINT16): {
      uint16_t ov = *(uint16_t *)val;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_INT8): {
          // check the range
          if (ov > INT8_MAX) {
            return 1;
          }
          *(int8_t *)out = (int8_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT16): {
          // check the range
          if (ov > INT16_MAX) {
            return 1;
          }
          *(int16_t *)out = (int16_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT32): {
          *(int32_t *)out = (int32_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT64): {
          *(int64_t *)out = (int64_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT8): {
          // check the range
          if (ov > UINT8_MAX) {
            return 1;
          }
          *(uint8_t *)out = (uint8_t)ov;
          return 0;
        }

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_UINT16): {
          *(uint16_t *)out = ov;
          return 0;
        }

        case (SMD_TYPE_UINT32): {
          *(uint32_t *)out = (uint32_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT64): {
          *(uint64_t *)out = (uint64_t)ov;
          return 0;
        }

        case (SMD_TYPE_FLOAT): {
          *(float *)out = (float)ov;
          return 0;
        }

        case (SMD_TYPE_DOUBLE): {
          *(double *)out = (double)ov;
          return 0;
        }

        case (SMD_TYPE_CHAR): {
          // check the range
          if (ov < SCHAR_MIN || ov > SCHAR_MAX) {
            return 1;
          }
          *(char *)out = (char)ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_UINT32): {
      uint32_t ov = *(uint32_t *)val;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_INT8): {
          // check the range
          if (ov > INT8_MAX) {
            return 1;
          }
          *(int8_t *)out = (int8_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT16): {
          // check the range
          if (ov > INT16_MAX) {
            return 1;
          }
          *(int16_t *)out = (int16_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT32): {
          // check the range
          if (ov > INT32_MAX) {
            return 1;
          }
          *(int32_t *)out = (int32_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT64): {
          *(int64_t *)out = (int64_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT8): {
          // check the range
          if (ov > UINT8_MAX) {
            return 1;
          }
          *(uint8_t *)out = (uint8_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT16): {
          // check the range
          if (ov > UINT16_MAX) {
            return 1;
          }
          *(uint16_t *)out = (uint16_t)ov;
          return 0;
        }

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_UINT32): {
          *(uint32_t *)out = ov;
          return 0;
        }

        case (SMD_TYPE_UINT64): {
          *(uint64_t *)out = (uint64_t)ov;
          return 0;
        }

        case (SMD_TYPE_FLOAT): {
          *(float *)out = (float)ov;
          return 0;
        }

        case (SMD_TYPE_DOUBLE): {
          *(double *)out = (double)ov;
          return 0;
        }

        case (SMD_TYPE_CHAR): {
          // check the range
          if (ov < SCHAR_MIN || ov > SCHAR_MAX) {
            return 1;
          }
          *(char *)out = (char)ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_UINT64): {
      uint64_t ov = *(uint64_t *)val;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_INT8): {
          // check the range
          if (ov > INT8_MAX) {
            return 1;
          }
          *(int8_t *)out = (int8_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT16): {
          // check the range
          if (ov > INT16_MAX) {
            return 1;
          }
          *(int16_t *)out = (int16_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT32): {
          // check the range
          if (ov > INT32_MAX) {
            return 1;
          }
          *(int32_t *)out = (int32_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT64): {
          // check the range
          if (ov > INT64_MAX) {
            return 1;
          }
          *(int64_t *)out = (int64_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT8): {
          // check the range
          if (ov > UINT8_MAX) {
            return 1;
          }
          *(uint8_t *)out = (uint8_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT16): {
          // check the range
          if (ov > UINT16_MAX) {
            return 1;
          }
          *(uint16_t *)out = (uint16_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT32): {
          // check the range
          if (ov > UINT32_MAX) {
            return 1;
          }
          *(uint32_t *)out = (uint32_t)ov;
          return 0;
        }

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_UINT64): {
          *(uint64_t *)out = ov;
          return 0;
        }

        case (SMD_TYPE_FLOAT): {
          *(float *)out = (float)ov;
          return 0;
        }

        case (SMD_TYPE_DOUBLE): {
          *(double *)out = (double)ov;
          return 0;
        }

        case (SMD_TYPE_CHAR): {
          // check the range
          if (ov < SCHAR_MIN || ov > SCHAR_MAX) {
            return 1;
          }
          *(char *)out = (char)ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_FLOAT): {
      float ov = *(float *)val;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_INT8): {
          // check the range
          if (ov < INT8_MIN || ov > INT8_MAX) {
            return 1;
          }
          *(int8_t *)out = (int8_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT16): {
          // check the range
          if (ov < INT16_MIN || ov > INT16_MAX) {
            return 1;
          }
          *(int16_t *)out = (int16_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT32): {
          // check the range
          if (ov < INT32_MIN || ov > INT32_MAX) {
            return 1;
          }
          *(int32_t *)out = (int32_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT64): {
          // check the range
          if (ov < INT64_MIN || ov > INT64_MAX) {
            return 1;
          }
          *(int64_t *)out = (int64_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT8): {
          // check the range
          if (ov < 0 || ov > UINT8_MAX) {
            return 1;
          }
          *(uint8_t *)out = (uint8_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT16): {
          // check the range
          if (ov < 0 || ov > UINT16_MAX) {
            return 1;
          }
          *(uint16_t *)out = (uint16_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT32): {
          // check the range
          if (ov < 0 || ov > UINT32_MAX) {
            return 1;
          }
          *(uint32_t *)out = (uint32_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT64): {
          // check the range
          if (ov < 0 || ov > UINT64_MAX) {
            return 1;
          }
          *(uint64_t *)out = (uint64_t)ov;
          return 0;
        }

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_FLOAT): {
          *(float *)out = ov;
          return 0;
        }

        case (SMD_TYPE_DOUBLE): {
          *(double *)out = (double)ov;
          return 0;
        }

        case (SMD_TYPE_CHAR): {
          // check the range
          if (ov < SCHAR_MIN || ov > SCHAR_MAX) {
            return 1;
          }
          *(char *)out = (char)ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_DOUBLE): {
      double ov = *(double *)val;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_INT8): {
          // check the range
          if (ov < INT8_MIN || ov > INT8_MAX) {
            return 1;
          }
          *(int8_t *)out = (int8_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT16): {
          // check the range
          if (ov < INT16_MIN || ov > INT16_MAX) {
            return 1;
          }
          *(int16_t *)out = (int16_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT32): {
          // check the range
          if (ov < INT32_MIN || ov > INT32_MAX) {
            return 1;
          }
          *(int32_t *)out = (int32_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT64): {
          // check the range
          if (ov < INT64_MIN || ov > INT64_MAX) {
            return 1;
          }
          *(int64_t *)out = (int64_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT8): {
          // check the range
          if (ov < 0 || ov > UINT8_MAX) {
            return 1;
          }
          *(uint8_t *)out = (uint8_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT16): {
          // check the range
          if (ov < 0 || ov > UINT16_MAX) {
            return 1;
          }
          *(uint16_t *)out = (uint16_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT32): {
          // check the range
          if (ov < 0 || ov > UINT32_MAX) {
            return 1;
          }
          *(uint32_t *)out = (uint32_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT64): {
          // check the range
          if (ov < 0 || ov > UINT64_MAX) {
            return 1;
          }
          *(uint64_t *)out = (uint64_t)ov;
          return 0;
        }

        case (SMD_TYPE_FLOAT): {
          // check the range
          if (ov < (double)FLT_MIN || ov > (double)FLT_MAX) {
            return 1;
          }
          *(float *)out = (float)ov;
          return 0;
        }

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_DOUBLE): {
          *(double *)out = ov;
          return 0;
        }

        case (SMD_TYPE_CHAR): {
          // check the range
          if (ov < SCHAR_MIN || ov > SCHAR_MAX) {
            return 1;
          }
          *(char *)out = (char)ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_CHAR): {
      char ov = *(char *)val;

      switch (usertype->type) {
        case (SMD_TYPE_EMPTY):

        case (SMD_TYPE_INT8): {
          *(int8_t *)out = (int8_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT16): {
          *(int16_t *)out = (int16_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT32): {
          *(int32_t *)out = (int32_t)ov;
          return 0;
        }

        case (SMD_TYPE_INT64): {
          *(int64_t *)out = (int64_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT8): {
          *(uint8_t *)out = (uint8_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT16): {
          *(uint16_t *)out = (uint16_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT32): {
          *(uint32_t *)out = (uint32_t)ov;
          return 0;
        }

        case (SMD_TYPE_UINT64): {
          *(uint64_t *)out = (uint64_t)ov;
          return 0;
        }

        case (SMD_TYPE_FLOAT): {
          *(float *)out = (float)ov;
          return 0;
        }

        case (SMD_TYPE_DOUBLE): {
          *(double *)out = (double)ov;
          return 0;
        }

        case (SMD_TYPE_AS_EXPECTED):

        case (SMD_TYPE_CHAR): {
          *(char *)out = ov;
          return 0;
        }

        default: {
          return 1;
        }
      }
    }

    case (SMD_TYPE_STRING): {
      char **p = (char **)val;
      //printf("RETRIEVE: %s: %lld\n", *p, val);
      *(char **)out = *p;
      return 0;
    }

    case (SMD_TYPE_EXTENT): {
      smd_dtype_extent_t *d = &t->specifier.u.ext;
      char *out_pos = out + d->lb;
      smd_attr_copy_val_to_external(out_pos, d->base, usertype, val);
      return 0;
    }

    case (SMD_TYPE_STRUCT): {
      smd_dtype_struct_t *d = &t->specifier.u.str;
      char *val_pos = val;
      for (int i = 0; i < d->size; i++) {
        char *out_pos = out + d->offsets[i];
        smd_attr_copy_val_to_external(out_pos, d->types[i], usertype, val_pos);
        val_pos += d->types[i]->size;
      }
      return 0;
    }

    case (SMD_TYPE_ARRAY): {
      smd_dtype_array_t *d = &t->specifier.u.arr;
      char *val_pos = val;
      char *out_pos = (char *)out;
      for (uint64_t i = 0; i < d->count; i++) {
        smd_attr_copy_val_to_external(out_pos, d->base, usertype, val_pos);
        out_pos += d->base->extent;
        val_pos += d->base->size;
      }
      return 0;
    }

    default:
      assert(0 && "SMD cannot copy unknown type");
  }
  return 0;
}

static void smd_free_type_str(smd_dtype_t *t, void *buff) {
  if (t->type == SMD_TYPE_STRING) {
    //printf("FREE: %p - %s\n", *(char**) buff, *(char**) buff);
    free(*(char **)buff);
  }
}

static void smd_attr_free_value(void *val, smd_dtype_t *dtype) {
  smd_basic_type_t type = dtype->type;

  switch (type) {
    case (SMD_TYPE_DTYPE):
      smd_type_unref((smd_dtype_t **)&val);
      break;
    case (SMD_TYPE_EMPTY):
    case (SMD_TYPE_INT8):
    case (SMD_TYPE_INT16):
    case (SMD_TYPE_INT32):
    case (SMD_TYPE_INT64):
    case (SMD_TYPE_UINT8):
    case (SMD_TYPE_UINT16):
    case (SMD_TYPE_UINT32):
    case (SMD_TYPE_UINT64):
    case (SMD_TYPE_FLOAT):
    case (SMD_TYPE_DOUBLE):
    case (SMD_TYPE_CHAR):
      break;
    case (SMD_TYPE_EXTENT):
      if (use_type_ptr(dtype)) {
        break;
      }
    case (SMD_TYPE_STRUCT):
    case (SMD_TYPE_ARRAY):
      // find all strings and free them.
      smd_type_iterate(dtype, (char *)val, smd_free_type_str);
    case (SMD_TYPE_STRING):
      free(val);
      break;
    default:
      assert(0 && "SMD cannot free unknown type");
  }
}

smd_attr_t *smd_attr_new_usertype(const char *name, smd_dtype_t *type, smd_dtype_t *usertype, const void *val) {
  smd_attr_t *attr = malloc(sizeof(smd_attr_t));
  assert(attr != NULL);
  memset(attr, 0, sizeof(smd_attr_t));
  attr->type = type;
  assert(name != NULL);
  int ret = 0;

  if (val != NULL) {
    smd_dtype_t *t = attr->type;
    if (type->type == SMD_TYPE_STRING) {
      attr->value = strdup((char *)val);
    } else if (use_type_ptr(t)) {
      ret = smd_attr_copy_val_to_internal((char *)&attr->value, type, usertype, val);
    } else {
      smd_attr_alloc(&attr->value, type);
      ret = smd_attr_copy_val_to_internal((char *)attr->value, type, usertype, val);
    }
  }

  if (ret != 0) {
    attr->name = NULL;
    smd_attr_destroy(attr);
    return NULL;
  }

  attr->name = smd_dup_escaped_varname(name);
  return attr;
}

smd_attr_t *smd_attr_new(const char *name, smd_dtype_t *type, const void *val) {
  return smd_attr_new_usertype(name, type, SMD_DTYPE_AS_EXPECTED, val);
}

void smd_attr_unlink_pos(smd_attr_t *p, unsigned int pos) {
  assert(p->children > pos);
  smd_attr_t *c = p->childs[pos];
  c->parent = NULL;

  p->childs[pos] = p->childs[p->children - 1];
  p->children--;
}

smd_link_ret_t smd_attr_link(smd_attr_t *parent, smd_attr_t *child, int allow_replace) {
  assert(child->parent == NULL);
  assert(child->name != NULL);
  // check if the child name is already taken
  int pos = smd_find_position_by_name(parent, child->name);
  if (pos != -1) {
    if (!allow_replace) {
      return SMD_ATTR_EEXIST;
    }
    smd_attr_destroy(parent->childs[pos]);
    parent->childs[pos] = child;
    child->parent = parent;
    return SMD_ATTR_REPLACED;
  }

  if (parent->childSlots == parent->children) { // init where?!
    if (parent->childs == NULL) {
      parent->childs = malloc(sizeof(void *) * 5); // why 5? no more than 5 children?
      parent->childSlots = 5;
    } else {
      // need to extend the existing structure
      parent->childSlots *= 2;
      smd_attr_t **new = malloc(sizeof(void *) * parent->childSlots); // why??
      for (unsigned int i = 0; i < parent->children; i++) {
        new[i] = parent->childs[i];
      }
      free(parent->childs);
      parent->childs = new;
    }
  }
  parent->childs[parent->children] = child;
  parent->children++; // where this was set to zero?!
  return SMD_ATTR_LINKED;
}

static void smd_attr_ser_json_str(smd_string_stream_t *s, const char *str, int len) {
  char const * end;
  if(len < 0) end = NULL;
  else end = str + len;

  if((end == NULL && *str == '\0') || (end != NULL && end == str)) {
    smd_string_stream_printf(s, "null");
    return;
  }

  smd_string_stream_printf(s, "\"");
  char c = *str;
  while (1) {
    if(end == NULL && c == '\0') break;

    switch (c) {
      case ('\0'): {
        smd_string_stream_printf(s, "\\0");
        str++;
        break;
      }
      case ('\b'): {
        smd_string_stream_printf(s, "\\b");
        str++;
        break;
      }
      case ('\f'): {
        smd_string_stream_printf(s, "\\f");
        str++;
        break;
      }
      case ('\n'): {
        smd_string_stream_printf(s, "\\n");
        str++;
        break;
      }
      case ('\r'): {
        smd_string_stream_printf(s, "\\r");
        str++;
        break;
      }
      case ('\t'): {
        smd_string_stream_printf(s, "\\t");
        str++;
        break;
      }
      case ('\"'): {
        smd_string_stream_printf(s, "\\\"");
        str++;
        break;
      }
      case ('\\'): {
        smd_string_stream_printf(s, "\\\\");
        str++;
        break;
      }
      default:
        smd_string_stream_printf(s, "%c", c);
        str++;
    }
    if(end != NULL && end == str) break;
    c = *str;
  }
  smd_string_stream_printf(s, "\"");
  return;
}

void smd_ser_json_value(smd_string_stream_t *s, void *val, smd_dtype_t *t) {
  switch (t->type) {
    case (SMD_TYPE_DTYPE):
      smd_string_stream_printf(s, "\"");
      smd_type_ser(s, *(smd_dtype_t **)val);
      smd_string_stream_printf(s, "\"");
      return;
    case (SMD_TYPE_EMPTY):
      smd_string_stream_printf(s, "null");
      return;
    case (SMD_TYPE_INT8):
      smd_string_stream_printf(s, "%d", *(int8_t *)val);
      return;
    case (SMD_TYPE_INT16):
      smd_string_stream_printf(s, "%d", *(int16_t *)val);
      return;
    case (SMD_TYPE_INT32):
      smd_string_stream_printf(s, "%d", *(int32_t *)val);
      return;
    case (SMD_TYPE_INT64):
      smd_string_stream_printf(s, "%ld", *(int64_t *)val);
      return;
    case (SMD_TYPE_UINT8):
      smd_string_stream_printf(s, "%u", *(uint8_t *)val);
      return;
    case (SMD_TYPE_UINT16):
      smd_string_stream_printf(s, "%u", *(uint16_t *)val);
      return;
    case (SMD_TYPE_UINT32):
      smd_string_stream_printf(s, "%u", *(uint32_t *)val);
      return;
    case (SMD_TYPE_UINT64):
      smd_string_stream_printf(s, "%lu", *(uint64_t *)val);
      return;
    case (SMD_TYPE_FLOAT):
      smd_string_stream_printf(s, "%.8e", (double)*(float *)val);
      return;
    case (SMD_TYPE_DOUBLE):
      smd_string_stream_printf(s, "%.16e", *(double *)val);
      return;
    case (SMD_TYPE_CHAR): {
      char c = *(char *)val;
      switch (c) {
        case ('\b'): {
          smd_string_stream_printf(s, "\"\\b\"");
          return;
        }
        case ('\f'): {
          smd_string_stream_printf(s, "\"\\f\"");
          return;
        }
        case ('\n'): {
          smd_string_stream_printf(s, "\"\\n\"");
          return;
        }
        case ('\r'): {
          smd_string_stream_printf(s, "\"\\r\"");
          return;
        }
        case ('\t'): {
          smd_string_stream_printf(s, "\"\\t\"");
          return;
        }
        case ('\"'): {
          smd_string_stream_printf(s, "\"\\\"\"");
          return;
        }
        case ('\\'): {
          smd_string_stream_printf(s, "\"\\\\\"");
          return;
        }
        case ('\0'): {
          smd_string_stream_printf(s, "null");
          return;
        }
        default:
          smd_string_stream_printf(s, "\"%c\"", c);
          return;
      }
    }
    case (SMD_TYPE_STRING): {
      smd_attr_ser_json_str(s, *(char **)val, -1);
      return;
    }
    case (SMD_TYPE_EXTENT): {
      smd_dtype_extent_t *d = &t->specifier.u.ext;
      smd_ser_json_value(s, val, d->base);
      return;
    }
    case (SMD_TYPE_STRUCT): {
      smd_dtype_struct_t *d = &t->specifier.u.str;
      smd_string_stream_printf(s, "{");
      char *val_pos = val;
      smd_attr_ser_json_str(s, d->names[0], -1);
      smd_string_stream_printf(s, ":");
      smd_ser_json_value(s, val_pos, d->types[0]);
      val_pos += d->types[0]->size;
      for (int i = 1; i < d->size; i++) {
        smd_string_stream_printf(s, ",");
        smd_attr_ser_json_str(s, d->names[i], -1);
        smd_string_stream_printf(s, ":");
        smd_ser_json_value(s, val_pos, d->types[i]);
        val_pos += d->types[i]->size;
      }
      smd_string_stream_printf(s, "}");
      return;
    }
    case (SMD_TYPE_ARRAY): {
      char *val_pos = val;
      smd_dtype_array_t *d = &t->specifier.u.arr;
      if(d->base->type == SMD_TYPE_CHAR){
        smd_attr_ser_json_str(s, val_pos, d->count);
        return;
      }

      smd_string_stream_printf(s, "[");
      if (d->count > 0) {
        smd_ser_json_value(s, val_pos, d->base);
        val_pos += d->base->size;
        for (uint64_t i = 1; i < d->count; i++) {
          smd_string_stream_printf(s, ",");
          smd_ser_json_value(s, val_pos, d->base);
          val_pos += d->base->size;
        }
      }
      smd_string_stream_printf(s, "]");
      return;
    }
    default:
      assert(0 && "SMD cannot serialize unknown type");
  }
}

void smd_attr_ser_json(smd_string_stream_t *s, smd_attr_t *attr) {
  //buff += smd_string_stream_printf(s, "{");
  smd_attr_ser_json_str(s, attr->name, -1);
  smd_string_stream_printf(s, ":{\"type\":\"");
  smd_type_ser(s, attr->type);
  smd_string_stream_printf(s, "\"");

  smd_string_stream_printf(s, ",\"data\":");
  if (use_type_ptr(attr->type)) {
    smd_ser_json_value(s, (char *)&attr->value, attr->type);
  } else {
    smd_ser_json_value(s, attr->value, attr->type);
  }
  if (attr->children) {
    smd_string_stream_printf(s, ",\"childs\":{");
    smd_attr_ser_json(s, attr->childs[0]);
    for (unsigned int i = 1; i < attr->children; i++) {
      smd_string_stream_printf(s, ",");
      smd_attr_ser_json(s, attr->childs[i]);
    }
    smd_string_stream_printf(s, "}");
  }
  smd_string_stream_printf(s, "}");
  //buff += smd_string_stream_printf(s, "}");
  return;
}

static char *smd_attr_string_from_json(char *out, char *str, int len) {
  char const * end;
  if(len < 0) end = NULL;
  else end = out + len;

  if (*str == 'n') {
    // could be null in JSON
    if (strncmp(str, "null", 4) == 0) {
      if(end == NULL) *out = 0;
      return str + 4;
    }
    return NULL;
  }
  if (*str != '\"') return NULL;
  str++;
  if(end != NULL && out == end) {
    // empty array!
    if (*str != '\"') return NULL;
    str++;
    return str;
  }

  // parse the JSON encoded string
  while (*str != '\"' && *str != 0) {
    if (*str == '\\') {
      // escape character
      str++;
      switch (*str) {
        case ('0'):
          *out = '\0';
          break;
        case ('b'):
          *out = '\b';
          break;
        case ('f'):
          *out = '\f';
          break;
        case ('n'):
          *out = '\n';
          break;
        case ('r'):
          *out = '\r';
          break;
        case ('t'):
          *out = '\t';
          break;
        case ('\"'):
          *out = '\"';
          break;
        case ('\\'):
          *out = '\\';
          break;
        default: // invalid!
          return NULL;
      }
      str++;
      out++;
      if(end != NULL && out == end) break;
      continue;
    }
    *out = *str;
    out++;
    str++;
    if(end != NULL && out == end) break;
  }

  if (*str != '\"') return NULL;
  str++;
  if(end == NULL) *out = 0;
  return str;
}

/*
 * Create a packed attribute value from the JSON
 */
static char *smd_attr_val_from_json(char *val, smd_dtype_t *t, char *str) {
  int c;
  switch (t->type) {
    case (SMD_TYPE_DTYPE): {
      if (*str != '"') return str;
      str++;
      char *pos = str;
      for (; *pos != '\"'; pos++)
        ;
      *pos = 0;
      smd_dtype_t *dtype = smd_type_from_ser(str);
      *(smd_dtype_t **)val = dtype;

      *pos = '\"';
      return pos + 1;
    }
    case (SMD_TYPE_EMPTY): {
      if (strncmp("null", str, 4) != 0) return NULL;
      return str + 4;
    }
    case (SMD_TYPE_UINT64): {
      uint64_t v;
      sscanf(str, "%lu%n", &v, &c);
      smd_attr_copy_val_to_internal((char *)val, t, t, &v);
      return str + c;
    }
    case (SMD_TYPE_INT64): {
      int64_t v;
      sscanf(str, "%ld%n", &v, &c);
      smd_attr_copy_val_to_internal((char *)val, t, t, &v);
      return str + c;
    }
    case (SMD_TYPE_INT8): {
      int v;
      sscanf(str, "%d%n", &v, &c);
      smd_attr_copy_val_to_internal((char *)val, t, t, &v);
      return str + c;
    }
    case (SMD_TYPE_INT16): {
      int v;
      sscanf(str, "%d%n", &v, &c);
      smd_attr_copy_val_to_internal((char *)val, t, t, &v);
      return str + c;
    }
    case (SMD_TYPE_UINT8): {
      unsigned v;
      sscanf(str, "%u%n", &v, &c);
      smd_attr_copy_val_to_internal((char *)val, t, t, &v);
      return str + c;
    }
    case (SMD_TYPE_UINT16): {
      unsigned v;
      sscanf(str, "%u%n", &v, &c);
      smd_attr_copy_val_to_internal((char *)val, t, t, &v);
      return str + c;
    }
    case (SMD_TYPE_UINT32): {
      unsigned v;
      sscanf(str, "%u%n", &v, &c);
      smd_attr_copy_val_to_internal((char *)val, t, t, &v);
      return str + c;
    }
    case (SMD_TYPE_INT32): {
      int v;
      sscanf(str, "%d%n", &v, &c);
      smd_attr_copy_val_to_internal((char *)val, t, t, &v);
      return str + c;
    }
    case (SMD_TYPE_FLOAT): {
      float v;
      sscanf(str, "%e%n", &v, &c);
      smd_attr_copy_val_to_internal((char *)val, t, t, &v);
      return str + c;
    }
    case (SMD_TYPE_DOUBLE): {
      double v;
      sscanf(str, "%le%n", &v, &c);
      smd_attr_copy_val_to_internal((char *)val, t, t, &v);
      return str + c;
    }
    case (SMD_TYPE_CHAR): {
      char buff[4096];
      str = smd_attr_string_from_json(buff, str, 1);
      if (str == NULL || buff[0] == 0) return NULL;
      char *c = (char *)val;
      *c = buff[0];
      return str;
    }
    case (SMD_TYPE_STRING): {
      char buff[4096];
      str = smd_attr_string_from_json(buff, str, -1);
      if (str[0] != 0) {
        *(char **)val = strdup(buff);
      } else {
        *(char **)val = 0;
      }
      return str;
    }
    case (SMD_TYPE_EXTENT): {
      smd_dtype_extent_t *d = &t->specifier.u.ext;
      return smd_attr_val_from_json(val, d->base, str);
    }
    case (SMD_TYPE_STRUCT): {
      char *out_pos = (char *)val;
      smd_dtype_struct_t *d = &t->specifier.u.str;
      if (*str != '{') return NULL;
      str++;
      int s;
      for (int i = 0; i < d->size; i++) {
        if (i > 0) {
          if (*str != ',') return NULL;
          str++;
        }
        if (*str != '"') return NULL;
        str++;
        s = strlen(d->names[i]);
        if (strncmp(str, d->names[i], s) != 0) return NULL;
        str += s;
        if (*str != '"') return NULL;
        str++;
        if (*str != ':') return NULL;
        str++;
        str = smd_attr_val_from_json(out_pos, d->types[i], str);
        out_pos += d->types[i]->size;
      }
      if (*str != '}') return NULL;
      str++;
      return str;
    }
    case (SMD_TYPE_ARRAY): {
      smd_dtype_array_t *d = &t->specifier.u.arr;
      char *out_pos = (char *)val;
      if(d->base->type == SMD_TYPE_CHAR){
        str = smd_attr_string_from_json(out_pos, str, d->count);
        return str;
      }

      if (*str != '[') return NULL;
      str++;
      if (d->count > 0) {
        for (uint64_t i = 0; i < d->count; i++) {
          if (i > 0) {
            if (*str != ',') return NULL;
            str++;
          }
          str = smd_attr_val_from_json(out_pos, d->base, str);
          out_pos += d->base->size;
        }
      }
      if (*str != ']') return NULL;
      str++;
      return str;
    }
    default:
      assert(0 && "SMD cannot convert unknown type from json");
  }

  return str;
}

char *smd_attr_create_from_json_i(char *str, smd_attr_t **attr_out, size_t size) {
  // TODO fix overflow
  assert(str != NULL);
  assert(attr_out != NULL);
  //printf("%d: \"%s\"\n", __LINE__, str);

  char aname[4096];
  str = smd_attr_string_from_json(aname, str, -1);
  if (str == NULL) return NULL;
  if (*str != ':') return NULL;
  str++;
  if (*str != '{') return NULL;
  str++;
  if (strncmp(str, "\"type\":\"", 8) != 0) return NULL;
  str += 8;
  smd_dtype_t *type = smd_type_from_ser_i(&str);
  if (type == NULL) return NULL;

  if (strncmp(str, "\",\"data\":", 9) != 0) {
    smd_type_destroy(type);
    return NULL;
  }
  str += 9;

  smd_attr_t *attr;
  attr = smd_attr_new(aname, type, NULL);

  void *val = NULL;
  if (use_type_ptr(attr->type)) {
    str = smd_attr_val_from_json((char *)&val, type, str);
  } else {
    smd_attr_alloc(&val, type);
    str = smd_attr_val_from_json(val, type, str);
  }
  attr->value = val;

  *attr_out = attr;
  //printf("%d: \"%s\"\n", __LINE__, str);
  if (*str == ',') {
    str++;
    // have children
    if (strncmp(str, "\"childs\":{", 10) != 0) {
      smd_type_destroy(type);
      return NULL;
    }
    str += 10;

    while (*str != '}') {
      smd_attr_t *child;
      str = smd_attr_create_from_json_i(str, &child, size);
      smd_attr_link(attr, child, 0); // why do we need this here??
      if (*str == ',') str++;
    }
    str++;
  }
  if (*str != '}') {
    smd_type_destroy(type);
    return NULL;
  }
  str++;

  return str;
}

size_t smd_attr_create_from_json(char *str, size_t length, smd_attr_t **out_attr) {
  if (length == 0) {
    *out_attr = NULL;
    return 0;
  }
  char *pos = smd_attr_create_from_json_i(str, out_attr, length);
  return (pos - str);
}

void smd_iterate(smd_attr_t *attr, void (*iter)(const char *name)) {
  iter(attr->name);
  for (unsigned int i = 0; i < attr->children; i++) {
    smd_iterate(attr->childs[i], iter);
  }
}

void smd_attr_destroy(smd_attr_t *attr) {
  if (attr->childs) {
    for (unsigned int i = 0; i < attr->children; i++) {
      smd_attr_destroy(attr->childs[i]);
    }
    free(attr->childs);
  }
  smd_attr_free_value(attr->value, attr->type);
  free((void *)attr->name);
  free(attr);
}

void *smd_attr_get_value(smd_attr_t *attr) {
  return attr->value;
}

const char *smd_attr_get_name(smd_attr_t *attr) {
  return attr->name;
}

void smd_attr_copy_value(smd_attr_t *attr, void *out_val) {
  assert(attr != NULL);
  if (use_type_ptr(attr->type)) {
    smd_attr_copy_val_to_external(out_val, attr->type, SMD_DTYPE_AS_EXPECTED, (char *)&attr->value);
  } else {
    smd_attr_copy_val_to_external(out_val, attr->type, SMD_DTYPE_AS_EXPECTED, attr->value);
  }
}

int smd_attr_copy_value_usertype(smd_attr_t *attr, smd_dtype_t *usertype, void *out_val) {
  assert(attr != NULL);
  if (use_type_ptr(attr->type)) {
    return smd_attr_copy_val_to_external(out_val, attr->type, usertype, (char *)&attr->value);
  } else {
    return smd_attr_copy_val_to_external(out_val, attr->type, usertype, attr->value);
  }
}

int smd_attr_count(const smd_attr_t *attr) {
  return attr->children;
}

smd_attr_t *smd_attr_get_child(const smd_attr_t *attr, unsigned int child) {
  assert(attr->children > child);
  return attr->childs[child];
}

smd_string_stream_t *smd_string_stream_create() {
  smd_string_stream_t *result = malloc(sizeof(*result));
  assert(result);
  *result = (smd_string_stream_t) {
  .string = NULL,
  .bufferSize = 0,
  .characterCount = 0,
  .stream = NULL};
  result->stream = open_memstream(&result->string, &result->bufferSize);
  assert(result->stream);
  return result;
}

void smd_string_stream_printf(smd_string_stream_t *stream, const char *format, ...) {
  assert(format);
  va_list args;
  va_start(args, format);
  int result = vfprintf(stream->stream, format, args);
  assert(result >= 0);
  stream->characterCount += result;
  va_end(args);
}

char *smd_string_stream_close(smd_string_stream_t *stream, size_t *out_size) {
  fclose(stream->stream);
  char *result = stream->string;
  if (out_size) *out_size = stream->characterCount;
  free(stream);
  return result;
}
