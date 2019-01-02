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

static size_t smd_escaped_str(char * buff, const char * name){
  // Generate a JSON conform name:
  //Backspace is replaced with space
  //Form feed is replaced with space
  //Newline is replaced with space
  //Carriage return is removed
  //Tab is replaced with space
  //Double quote is remoevd
  //Backslash is removed
  char * oldb = buff;
  for(int i=0; name[i] != 0; i++){
    *buff = name[i];
    buff++;
  }
  return buff - oldb;
}


smd_dtype_t * smd_type_from_ser_i(char ** str){
  char type = **str - 'a';
  (*str)++;
  switch(type){
    case(SMD_TYPE_INT8):
      return SMD_DTYPE_INT8;
    case(SMD_TYPE_INT16):
      return SMD_DTYPE_INT16;
    case(SMD_TYPE_INT32):
      return SMD_DTYPE_INT32;
    case(SMD_TYPE_INT64):
      return SMD_DTYPE_INT64;
    case(SMD_TYPE_UINT8):
      return SMD_DTYPE_UINT8;
    case(SMD_TYPE_UINT16):
      return SMD_DTYPE_UINT16;
    case(SMD_TYPE_UINT32):
      return SMD_DTYPE_UINT32;
    case(SMD_TYPE_UINT64):
      return SMD_DTYPE_UINT64;
    case(SMD_TYPE_FLOAT):
      return SMD_DTYPE_FLOAT;
    case(SMD_TYPE_DOUBLE):
      return SMD_DTYPE_DOUBLE;
    case(SMD_TYPE_CHAR):
      return SMD_DTYPE_CHAR;
    case(SMD_TYPE_STRING):
      return SMD_DTYPE_STRING;
    case(SMD_TYPE_EXTENT):{
      size_t lb;
      size_t ub;
      int pos = 0;
      sscanf(*str, "%zu@%zu,%n", & lb, & ub, &pos);
      *str += pos;
      smd_dtype_t * base_type = smd_type_from_ser_i(str);
      if(base_type == NULL){
        return NULL;
      }
      return smd_type_extent(lb, ub, base_type);
    }case(SMD_TYPE_STRUCT):{
      size_t nmeb;
      size_t extent;
      int pos = 0;
      sscanf(*str, "%zu@%zu@%n", & nmeb, & extent, &pos);
      *str += pos;
      if(nmeb < 1 || extent < 1) return NULL;
      char ** names = malloc(sizeof(char*) * nmeb);
      size_t * offsets = malloc(sizeof(size_t) * nmeb);
      smd_dtype_t ** types = malloc(sizeof(char*) * nmeb);
      for(int i=0; i < nmeb; i++){
        // name, offset
        char * name = *str;
        while(*name != 0 && *name != '@') name++;
        if(*name == 0) return NULL;
        *name = 0;
        names[i] = strdup(*str);
        *name = '@';
        *str = name + 1;
        sscanf(*str, "%zu,%n", & offsets[i], &pos);
        *str += pos;
        types[i] = smd_type_from_ser_i(str);
      }
      smd_dtype_t * str = smd_type_struct(nmeb, offsets, extent, names, types);
      for(int i=0; i < nmeb; i++){
        free(names[i]);
      }
      free(types);
      free(names);
      free(offsets);
      return str;
    }case(SMD_TYPE_ARRAY):{
      size_t nmeb;
      int pos = 0;
      sscanf(*str, "%zu@%n", & nmeb, &pos);
      *str += pos;
      if(nmeb < 0) return NULL;
      smd_dtype_t * base_type = smd_type_from_ser_i(str);
      if(base_type == NULL){
        return NULL;
      }
      return smd_type_array(base_type, nmeb);
    }default:
       return NULL;
  }
}

smd_dtype_t * smd_type_from_ser(char * str){
  return smd_type_from_ser_i(& str);
}

size_t smd_type_ser_i(char * buff, smd_dtype_t * t){
    smd_basic_type_t type = t->type;
    *buff = type + 'a';
  	switch(type){
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
      case(SMD_TYPE_INT8):
        return 1;
  		case(SMD_TYPE_EXTENT):{
        char * oldb = buff;
        buff++;
        smd_dtype_extent_t * d = & t->specifier.u.ext;
        buff += sprintf(buff, "%zu@%zu,", d->lb, t->extent);
        buff += smd_type_ser(buff, d->base);
        return buff - oldb;
  		}case(SMD_TYPE_STRUCT):{
        char * oldb = buff;
        buff++;
        smd_dtype_struct_t * d = & t->specifier.u.str;
        buff += sprintf(buff, "%d@%zu@", d->size, t->extent);
        buff += sprintf(buff, "%s@%zu,", d->names[0], d->offsets[0]);
        buff += smd_type_ser_i(buff, d->types[0]);
        for(int i = 1; i < d->size; i++){
          buff += sprintf(buff, "%s@%zu,", d->names[i], d->offsets[i]);
          buff += smd_type_ser_i(buff, d->types[i]);
        }
        return buff - oldb;
  		}case(SMD_TYPE_ARRAY):{
        char * oldb = buff;
        buff++;
        smd_dtype_array_t * d = & t->specifier.u.arr;
        buff += sprintf(buff, "%zu@", d->count);
        buff += smd_type_ser_i(buff, d->base);
        return buff - oldb;
  		}default:
  			assert(0 && "SMD cannot print unknown type");
  	}
}

size_t smd_type_ser(char * buff, smd_dtype_t * t){
  size_t len = smd_type_ser_i(buff, t);
  buff[len] = 0;
  return len + 1;
}

static size_t smd_type_print_i(char * buff, smd_dtype_t * t){
    smd_basic_type_t type = t->type;
  	switch(type){
      case(SMD_TYPE_INT8):
        return sprintf(buff, "I08");
      case(SMD_TYPE_INT16):
        return sprintf(buff, "I16");
      case(SMD_TYPE_INT32):
        return sprintf(buff, "I32");
      case(SMD_TYPE_INT64):
        return sprintf(buff, "I64");
      case(SMD_TYPE_UINT8):
        return sprintf(buff, "U08");
      case(SMD_TYPE_UINT16):
        return sprintf(buff, "U16");
      case(SMD_TYPE_UINT32):
        return sprintf(buff, "U32");
      case(SMD_TYPE_UINT64):
        return sprintf(buff, "U64");
      case(SMD_TYPE_FLOAT):
        return sprintf(buff, "FLT");
      case(SMD_TYPE_DOUBLE):
        return sprintf(buff, "DBL");
      case(SMD_TYPE_CHAR):
        return sprintf(buff, "CHA");
  		case(SMD_TYPE_EXTENT):{
        char * oldb = buff;
        smd_dtype_extent_t * d = & t->specifier.u.ext;
        buff += sprintf(buff, "EXT");
        buff += sprintf(buff, "(%zu,%zu,", d->lb, t->extent);
        buff += smd_type_print_i(buff, d->base);
        buff += sprintf(buff, ")");
        return buff - oldb;
  		}case(SMD_TYPE_STRUCT):{
        char * oldb = buff;
        smd_dtype_struct_t * d = & t->specifier.u.str;
        buff += sprintf(buff, "STT");
        buff += sprintf(buff, "(%d,[", d->size);
        buff += sprintf(buff, "\"%s\":%zu,", d->names[0], d->offsets[0]);
        buff += smd_type_print_i(buff, d->types[0]);
        for(int i = 1; i < d->size; i++){
          buff += sprintf(buff, ",\"%s\":%zu,", d->names[i], d->offsets[i]);
          buff += smd_type_print_i(buff, d->types[i]);
        }
        buff += sprintf(buff, "])");
        return buff - oldb;
  		}case(SMD_TYPE_ARRAY):{
        char * oldb = buff;
        smd_dtype_array_t * d = & t->specifier.u.arr;
        buff += sprintf(buff, "ARR");
        buff += sprintf(buff, "(%zu,", d->count);
        buff += smd_type_print_i(buff, d->base);
        buff += sprintf(buff, ")");
        return buff - oldb;
  		}case(SMD_TYPE_STRING):
        return sprintf(buff, "STR");
  		default:
  			assert(0 && "SMD cannot print unknown type");
  	}
}

size_t smd_type_print(char * buff, smd_dtype_t * t){
  size_t len = smd_type_print_i(buff, t);
  buff[len] = 0;
  return len + 1;
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
    assert(names[i] != NULL);
    new->names[i] = smd_dup_escaped_varname(names[i]);
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
