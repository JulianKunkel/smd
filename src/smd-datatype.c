#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <smd-internal.h>


/**
 * Primitive datatypes
 */

static smd_dtype_t SMD_DTYPE_UNKNOWN_d = {.type = SMD_TYPE_UNKNOWN, .refcount = 1, .size = -1, .extent = -1};
smd_dtype_t * SMD_DTYPE_UNKNOWN = & SMD_DTYPE_UNKNOWN_d;

static smd_dtype_t SMD_DTYPE_INT8_d = {.type = SMD_TYPE_INT8, .refcount = 1, .size = sizeof(int8_t), .extent = sizeof(int8_t)};
smd_dtype_t * SMD_DTYPE_INT8 = & SMD_DTYPE_INT8_d;

static smd_dtype_t SMD_DTYPE_INT16_d = {.type = SMD_TYPE_INT16, .refcount = 1, .size = sizeof(int16_t), .extent = sizeof(int16_t)};
smd_dtype_t * SMD_DTYPE_INT16 = & SMD_DTYPE_INT16_d;

static smd_dtype_t SMD_DTYPE_INT32_d = {.type = SMD_TYPE_INT32, .refcount = 1, .size = sizeof(int32_t), .extent = sizeof(int32_t)};
smd_dtype_t * SMD_DTYPE_INT32 = & SMD_DTYPE_INT32_d;

static smd_dtype_t SMD_DTYPE_INT64_d = {.type = SMD_TYPE_INT64, .refcount = 1, .size = sizeof(int64_t), .extent = sizeof(int64_t)};
smd_dtype_t * SMD_DTYPE_INT64 = & SMD_DTYPE_INT64_d;

static smd_dtype_t SMD_DTYPE_UINT8_d = {.type = SMD_TYPE_UINT8, .refcount = 1, .size = sizeof(uint8_t), .extent = sizeof(uint8_t)};
smd_dtype_t * SMD_DTYPE_UINT8 = & SMD_DTYPE_UINT8_d;

static smd_dtype_t SMD_DTYPE_UINT16_d = {.type = SMD_TYPE_UINT16, .refcount = 1, .size = sizeof(uint16_t), .extent = sizeof(uint16_t)};
smd_dtype_t * SMD_DTYPE_UINT16 = & SMD_DTYPE_UINT16_d;

static smd_dtype_t SMD_DTYPE_UINT32_d = {.type = SMD_TYPE_UINT32, .refcount = 1, .size = sizeof(uint32_t), .extent = sizeof(uint32_t)};
smd_dtype_t * SMD_DTYPE_UINT32 = & SMD_DTYPE_UINT32_d;

static smd_dtype_t SMD_DTYPE_UINT64_d = {.type = SMD_TYPE_UINT64, .refcount = 1, .size = sizeof(uint64_t), .extent = sizeof(uint64_t)};
smd_dtype_t * SMD_DTYPE_UINT64 = & SMD_DTYPE_UINT64_d;

static smd_dtype_t SMD_DTYPE_FLOAT_d = {.type = SMD_TYPE_FLOAT, .refcount = 1, .size = sizeof(float), .extent = sizeof(float)};
smd_dtype_t * SMD_DTYPE_FLOAT = & SMD_DTYPE_FLOAT_d;

static smd_dtype_t SMD_DTYPE_DOUBLE_d = {.type = SMD_TYPE_DOUBLE, .refcount = 1, .size = sizeof(double), .extent = sizeof(double)};
smd_dtype_t * SMD_DTYPE_DOUBLE = & SMD_DTYPE_DOUBLE_d;

static smd_dtype_t SMD_DTYPE_CHAR_d = {.type = SMD_TYPE_CHAR, .refcount = 1, .size = sizeof(char), .extent = sizeof(char)};
smd_dtype_t * SMD_DTYPE_CHAR = & SMD_DTYPE_CHAR_d;

static smd_dtype_t SMD_DTYPE_STRING_d = {.type = SMD_TYPE_STRING, .refcount = 1, .size = sizeof(char*), .extent = sizeof(char*)};
smd_dtype_t * SMD_DTYPE_STRING = & SMD_DTYPE_STRING_d;

static smd_dtype_t SMD_DTYPE_UB_d = {.type = SMD_TYPE_UB, .refcount = 1, .size = 0, .extent = 0};
smd_dtype_t * SMD_DTYPE_UB = & SMD_DTYPE_UB_d;
static smd_dtype_t SMD_DTYPE_LB_d = {.type = SMD_TYPE_LB, .refcount = 1, .size = 0, .extent = 0};
smd_dtype_t * SMD_DTYPE_LB = & SMD_DTYPE_LB_d;


void smd_type_destroy(smd_dtype_t * type){
  if(type->refcount > 0){
    printf("SMD FATAL: refcount > 0\n");
    exit(1);
  }
  if(type->type < SMD_TYPE_PRIMITIVE_END){
    free(type);
    return;
  }
  switch(type->type){
    case(SMD_TYPE_EXTENT):
      smd_type_unref(& type->specifier.u.ext.base);
      break;
    case(SMD_TYPE_ARRAY):
      smd_type_unref(& type->specifier.u.arr.base);
      break;
    case(SMD_TYPE_STRUCT):{
      smd_dtype_struct_t * str = & type->specifier.u.str;
      for(int i=0; i < str->size; i++){
        smd_type_unref(& str->types[i]);
        if(str->names[i]){
          free((void*) str->names[i]);
        }
      }
      free(str->names);
      break;
    }default:
      assert(0 && "Not Implemented");
  }
  free(type);
}

void smd_type_unref(smd_dtype_t ** type){
  if(type == NULL){
    return;
  }
  (*type)->refcount--;
  if((*type)->refcount == 0){
    smd_type_destroy(*type);
    *type = NULL;
  }
}

void smd_type_printer(smd_dtype_t * t){
    smd_basic_type_t type = t->type;
  	switch(type){
  		case(SMD_TYPE_INT8):
        printf("INT8");
        break;
  		case(SMD_TYPE_INT16):
        printf("INT16");
        break;
  		case(SMD_TYPE_INT32):
        printf("INT32");
        break;
  		case(SMD_TYPE_INT64):
        printf("INT64");
        break;
  		case(SMD_TYPE_UINT8):
        printf("UINT8");
        break;
  		case(SMD_TYPE_UINT16):
        printf("UINT16");
        break;
  		case(SMD_TYPE_UINT32):
        printf("UINT32");
        break;
  		case(SMD_TYPE_UINT64):
        printf("UINT64");
        break;
  		case(SMD_TYPE_FLOAT):
        printf("FLOAT");
        break;
  		case(SMD_TYPE_DOUBLE):
        printf("DOUBLE");
        break;
  		case(SMD_TYPE_CHAR):
        printf("CHAR");
        break;
  		case(SMD_TYPE_EXTENT):{
        smd_dtype_extent_t * d = & t->specifier.u.ext;
        printf("EXTENT");
        printf("(%zu,", d->lb);
        smd_type_printer(d->base);
        printf(")");
        break;
  		}case(SMD_TYPE_STRUCT):{
        smd_dtype_struct_t * d = & t->specifier.u.str;
        printf("STRUCT");
        printf("(%d, [", d->size);
        smd_type_printer(d->types[0]);
        for(int i = 1; i < d->size; i++){
          printf(",");
          smd_type_printer(d->types[i]);
        }
        printf("])");
        break;
  		}case(SMD_TYPE_ARRAY):{
        smd_dtype_array_t * d = & t->specifier.u.arr;
        printf("ARRAY");
        printf("(%zu,", d->count);
        smd_type_printer(d->base);
        printf(")");
        break;
  		}case(SMD_TYPE_STRING):
        printf("STRING");
        break;
  		default:
  			assert(0 && "SMD cannot print unknown type");
  	}
}


void smd_type_iterate(smd_dtype_t * t, char * buff, void (*iter)(smd_dtype_t * t, void * buff)){
	smd_basic_type_t type = t->type;
  iter(t, buff);
	switch(type){
			case(SMD_TYPE_INT8):
			case(SMD_TYPE_INT16):
			case(SMD_TYPE_INT32):
			case(SMD_TYPE_INT64):
			case(SMD_TYPE_UINT8):
			case(SMD_TYPE_UINT16):
			case(SMD_TYPE_UINT32):
			case(SMD_TYPE_UINT64):
			case(SMD_TYPE_FLOAT):
			case(SMD_TYPE_DOUBLE):
			case(SMD_TYPE_CHAR):
      case(SMD_TYPE_STRING):
				return;
			case(SMD_TYPE_EXTENT):{
        smd_dtype_extent_t * d = & t->specifier.u.ext;
        smd_type_iterate(d->base, buff, iter);
        return;
			}case(SMD_TYPE_STRUCT):{
				smd_dtype_struct_t * d = & t->specifier.u.str;
				char * val_pos = buff;
				for(int i = 0; i < d->size; i++){
          smd_type_iterate(d->types[i], val_pos, iter);
					val_pos += d->types[i]->size;
				}
				return;
			}case(SMD_TYPE_ARRAY):{
				smd_dtype_array_t * d = & t->specifier.u.arr;
				char * val_pos = buff;
				for(int i=0; i < d->count; i++){
          smd_type_iterate(d->base, val_pos, iter);
					val_pos += d->base->size;
				}
				return;
      }default:
			   assert(0 && "SMD cannot free unknown type");
	}
}

smd_dtype_t * smd_type_extent(size_t lb, size_t ub, smd_dtype_t * base_type){
  assert(base_type != NULL);

  smd_dtype_t * t = malloc(sizeof(smd_dtype_t));
  memset(t, 0, sizeof(smd_dtype_t));

  t->type = SMD_TYPE_EXTENT;
  t->refcount = 1;

  smd_dtype_extent_t * new = & t->specifier.u.ext;
  new->base = base_type;
  new->lb = lb;
  base_type->refcount++;

  assert(ub >= base_type->size + lb);
  t->size = base_type->size;
  t->extent = ub;

  return t;
}

smd_dtype_t * smd_type_array(smd_dtype_t * base_type, uint64_t nmeb){
  assert(base_type != NULL);
  assert(nmeb >= 0);

  smd_dtype_t * t = malloc(sizeof(smd_dtype_t));
  memset(t, 0, sizeof(smd_dtype_t));

  t->type = SMD_TYPE_ARRAY;
  t->refcount = 1;

  smd_dtype_array_t * new = & t->specifier.u.arr;
  new->base = base_type;
  new->count = nmeb;
  base_type->refcount++;

  t->size = base_type->size * nmeb;
  t->extent = base_type->extent * nmeb;

  return t;
}

smd_dtype_t * smd_type_struct(int nmeb, size_t * offsets, size_t extent, char * const * names, smd_dtype_t ** types){
  assert(nmeb > 0);
  assert(types != NULL);
  assert(offsets != NULL);
  assert(names != NULL);

  smd_dtype_t * t = malloc(sizeof(smd_dtype_t));
  memset(t, 0, sizeof(smd_dtype_t));

  t->type = SMD_TYPE_STRUCT;
  t->refcount = 1;

  smd_dtype_struct_t * new = & t->specifier.u.str;
  new->size = nmeb;
  new->names = malloc(sizeof(void*) * nmeb * 3);
  new->types = (smd_dtype_t**)(new->names + nmeb);
  new->offsets = (size_t*)    (new->names + 2*nmeb);

  size_t last_offset = 0;
  size_t size = 0;

  for(int i=0; i < nmeb; i++){
    assert(types[i] != NULL);

    if(names[i] != NULL){
      new->names[i] = strdup(names[i]);
    }else{
      new->names[i] = NULL;
    }
    new->types[i] = types[i];
    new->offsets[i] = offsets[i];

    assert(last_offset <= offsets[i]);
    last_offset = offsets[i] + types[i]->size;

    size += types[i]->size;

    types[i]->refcount++;
  }

  t->size   = size;
  assert(last_offset <= extent);
  t->extent = extent;

  return t;
}

size_t smd_type_get_size(smd_dtype_t * type){
    return type->size;
}

size_t smd_type_get_extent(smd_dtype_t * type){
  return type->extent;
}
