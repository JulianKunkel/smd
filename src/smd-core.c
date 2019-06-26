#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <smd-internal.h>


#define use_type_ptr(t) (t->type < SMD_TYPE_PRIMITIVE_END || (t->type == SMD_TYPE_EXTENT && t->specifier.u.ext.base->type < SMD_TYPE_PRIMITIVE_END))

// Native Datatypes ///////////////////////////////////////////////////////////
static size_t smd_sizeof(smd_basic_type_t type) {
	switch (type) {
		case SMD_TYPE_DTYPE:
			return sizeof(void*);
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

char * smd_dup_escaped_varname(const char * name){
  //Generate a conform variable name removing all non-printable characters
	int len = strlen(name);// max length
	char * buff = malloc(len + 1);
	int i;
	char * orig = buff;
  for(i=0; name[i] != 0; i++){
		char c = name[i];
		if(c < 32 || c > 127 || c == 92 || c == 34 || c == 64 ){
			continue;
		}
    *buff = name[i];
		buff++;
  }
	*buff = 0;
  return orig;
}

int smd_find_position_by_name(const smd_attr_t * attr, const char * name){
	for(unsigned  int i=0; i < attr->children; i++){
		if(strcmp(attr->childs[i]->name, name) == 0){
			return i;
		}
	}
	return -1;
}

int smd_find_position_by_id(const smd_attr_t * attr, int id){
	for(unsigned int i=0; i < attr->children; i++){
		if(attr->childs[i]->id == id){
			return i;
		}
	}
	return -1;
}


static void smd_attr_alloc(void ** out, smd_dtype_t * dtype){
	smd_basic_type_t type = dtype->type;
	switch(type){
		case(SMD_TYPE_EXTENT):
		case(SMD_TYPE_STRUCT):
		case(SMD_TYPE_ARRAY):{
			*out = malloc(dtype->size);
			//printf("alloced %ld to %ld\n", dtype->size, *out);
			return;
		}
		default:
			return;
	}
}

static void smd_attr_copy_val_to_internal(char * out, smd_dtype_t * t, const void * val){
	smd_basic_type_t type = t->type;
	//printf("E=>I %d %lld %lld\n", type, out, val);
	switch(type){
			case(SMD_TYPE_DTYPE):{
				smd_dtype_t ** p = (smd_dtype_t**) out;
				*p = (smd_dtype_t*) val;
				(*p)->refcount++;
				break;
			}case(SMD_TYPE_INT8):{
				int8_t * p = (int8_t*) out;
				*p = *(int8_t*) val;
				break;
			}case(SMD_TYPE_INT16):{
			  int16_t * p = (int16_t*) out;
			  *p = *(int16_t*) val;
			  break;
			}case(SMD_TYPE_INT32):{
			  int32_t * p = (int32_t*) out;
			  *p = *(int32_t*) val;
			  break;
			}case(SMD_TYPE_INT64):{
			  int64_t * p = (int64_t*) out;
			  *p = *(int64_t*) val;
			  break;
			}case(SMD_TYPE_UINT8):{
			  uint8_t * p = (uint8_t*) out;
			  *p = *(uint8_t*) val;
			  break;
			}case(SMD_TYPE_UINT16):{
			  uint16_t * p = (uint16_t*) out;
			  *p = *(uint16_t*) val;
			  break;
			}case(SMD_TYPE_UINT32):{
			  uint32_t * p = (uint32_t*) out;
			  *p = *(uint32_t*) val;
			  break;
			}case(SMD_TYPE_UINT64):{
			  uint64_t * p = (uint64_t*) out;
			  *p = *(uint64_t*) val;
			  break;
			}case(SMD_TYPE_FLOAT):{
			  float * p = (float*) out;
			  *p = *(float*) val;
			  break;
			}case(SMD_TYPE_DOUBLE):{
			  double * p = (double*) out;
			  *p = *(double*) val;
			  break;
			}case(SMD_TYPE_CHAR):{
			  char * p = (char*) out;
			  *p = *(char*) val;
			  break;
			}case(SMD_TYPE_STRING):{
				char ** p = (char **) out;
				*p = strdup((char*) val);
				//printf("STR %lld: %s %ld = %s\n", out, val, val, *((char**)out));
				break;
			}case(SMD_TYPE_EXTENT):{
				smd_dtype_extent_t * d = & t->specifier.u.ext;
				char * pos = (char*) val + d->lb;
				smd_attr_copy_val_to_internal(out, d->base, pos);
				return;
			}case(SMD_TYPE_STRUCT):{
				smd_dtype_struct_t * d = & t->specifier.u.str;
				char * out_pos = (char*) out;
				for(int i = 0; i < d->size; i++){
					char * val_pos = (char*) val + d->offsets[i];
					smd_attr_copy_val_to_internal(out_pos, d->types[i], val_pos);
					out_pos += d->types[i]->size;
				}
				return;
			}case(SMD_TYPE_ARRAY):{
				smd_dtype_array_t * d = & t->specifier.u.arr;
				char * val_pos = (char*) val;
				char * out_pos = (char*) out;
				for(uint64_t i=0; i < d->count; i++){
					smd_attr_copy_val_to_internal(out_pos, d->base, val_pos);
					if(d->base->type == SMD_TYPE_STRING){
						smd_attr_copy_val_to_internal(out_pos, d->base, *(char**) val_pos);
					}else{
						smd_attr_copy_val_to_internal(out_pos, d->base, val_pos);
					}
					out_pos += d->base->size;
					val_pos += d->base->extent;
				}
				return;
			}
		default:
			assert(0 && "SMD cannot copy unknown type");
	}
}


static void smd_attr_copy_val_to_external(char * out, smd_dtype_t * t, char * val){
	smd_basic_type_t type = t->type;
	//printf("I=>E %d %lld %lld\n", type, val, out);

	switch(type){
		  case(SMD_TYPE_INT8):{
		    int8_t * p = (int8_t*) val;
		    *(int8_t*) out = *p;
		    break;
		  }case(SMD_TYPE_INT16):{
		    int16_t * p = (int16_t*) val;
		    *(int16_t*) out = *p;
		    break;
		  }case(SMD_TYPE_INT32):{
		    int32_t * p = (int32_t*) val;
		    *(int32_t*) out = *p;
		    break;
		  }case(SMD_TYPE_INT64):{
		    int64_t * p = (int64_t*) val;
		    *(int64_t*) out = *p;
		    break;
		  }case(SMD_TYPE_UINT8):{
		    uint8_t * p = (uint8_t*) val;
		    *(uint8_t*) out = *p;
		    break;
		  }case(SMD_TYPE_UINT16):{
		    uint16_t * p = (uint16_t*) val;
		    *(uint16_t*) out = *p;
		    break;
		  }case(SMD_TYPE_UINT32):{
		    uint32_t * p = (uint32_t*) val;
		    *(uint32_t*) out = *p;
		    break;
		  }case(SMD_TYPE_UINT64):{
		    uint64_t * p = (uint64_t*) val;
		    *(uint64_t*) out = *p;
		    break;
		  }case(SMD_TYPE_FLOAT):{
		    float * p = (float*) val;
		    *(float*) out = *p;
		    break;
		  }case(SMD_TYPE_DOUBLE):{
		    double * p = (double*) val;
		    *(double*) out = *p;
		    break;
		  }case(SMD_TYPE_CHAR):{
		    char * p = (char*) val;
		    *(char*) out = *p;
		    break;
		  }case(SMD_TYPE_STRING):{
				char ** p = (char**) val;
				//printf("RETRIEVE: %s: %lld\n", *p, val);
				*(char**) out = *p;
				break;
			}case(SMD_TYPE_EXTENT):{
				smd_dtype_extent_t * d = & t->specifier.u.ext;
				char * out_pos = out + d->lb;
				smd_attr_copy_val_to_external(out_pos, d->base, val);
				return;
			}case(SMD_TYPE_STRUCT):{
				smd_dtype_struct_t * d = & t->specifier.u.str;
				char * val_pos = val;
				for(int i = 0; i < d->size; i++){
					char * out_pos = out + d->offsets[i];
					smd_attr_copy_val_to_external(out_pos, d->types[i], val_pos);
					val_pos += d->types[i]->size;
				}
				return;
			}case(SMD_TYPE_ARRAY):{
				smd_dtype_array_t * d = & t->specifier.u.arr;
				char * val_pos = val;
				char * out_pos = (char*) out;
				for(uint64_t i=0; i < d->count; i++){
					smd_attr_copy_val_to_external(out_pos, d->base, val_pos);
					out_pos += d->base->extent;
					val_pos += d->base->size;
				}
				return;
			}
		default:
			assert(0 && "SMD cannot copy unknown type");
	}
}

static void smd_free_type_str(smd_dtype_t * t, void * buff){
	if(t->type == SMD_TYPE_STRING){
		//printf("FREE: %p - %s\n", *(char**) buff, *(char**) buff);
		free(*(char**) buff);
	}
}

static void smd_attr_free_value(void * val, smd_dtype_t * dtype){
	smd_basic_type_t type = dtype->type;

	switch(type){
			case(SMD_TYPE_DTYPE):
				smd_type_unref((smd_dtype_t**) & val);
				break;
			case(SMD_TYPE_EMPTY):
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
				break;
			case(SMD_TYPE_EXTENT):
				if(use_type_ptr(dtype)){
					break;
				}
			case(SMD_TYPE_STRUCT):
			case(SMD_TYPE_ARRAY):
				// find all strings and free them.
				smd_type_iterate(dtype, (char*) val, smd_free_type_str);
			case(SMD_TYPE_STRING):
				free(val);
				break;
		default:
			assert(0 && "SMD cannot free unknown type");
	}
}

smd_attr_t * smd_attr_new(const char* name, smd_dtype_t * type, const void * val, int id){
	smd_attr_t * attr = malloc(sizeof(smd_attr_t));
	assert(attr != NULL);
	memset(attr, 0, sizeof(smd_attr_t));
	attr->id = id;
	attr->type = type;
	assert(name != NULL);

	if(val != NULL){
		smd_dtype_t * t = attr->type;
		if(type->type == SMD_TYPE_STRING){
			attr->value = strdup((char*) val);
		}else if(use_type_ptr(t)){
			smd_attr_copy_val_to_internal((char*) & attr->value, type, val);
		}else{
			smd_attr_alloc(& attr->value, type);
			smd_attr_copy_val_to_internal((char*) attr->value, type, val);
		}
	}

	attr->name = smd_dup_escaped_varname(name);
	return attr;
}

void smd_attr_unlink_pos(smd_attr_t * p, unsigned int pos){
	assert(p->children > pos);
	smd_attr_t * c = p->childs[pos];
	c->parent = NULL;

	p->childs[pos] = p->childs[p->children - 1];
	p->children--;
}

smd_link_ret_t smd_attr_link(smd_attr_t * parent, smd_attr_t * child, int allow_replace){
	assert(child->parent == NULL);
	assert(child->name != NULL);
	// check if the child name is already taken
	int pos = smd_find_position_by_name(parent, child->name);
	if(pos != -1){
		if(! allow_replace){
			return SMD_ATTR_EEXIST;
		}
		smd_attr_destroy(parent->childs[pos]);
		parent->childs[pos] = child;
		child->parent = parent;
		return SMD_ATTR_REPLACED;
	}

	if(parent->childSlots == parent->children){
		if(parent->childs == NULL){
			parent->childs = malloc(sizeof(void*) * 5);
			parent->childSlots = 5;
		}else{
			// need to extend the existing structure
			parent->childSlots *= 2;
			smd_attr_t ** new = malloc(sizeof(void*) * parent->childSlots);
			for(unsigned int i=0; i < parent->children; i++){
				new[i] = parent->childs[i];
			}
			free(parent->childs);
			parent->childs = new;
		}
	}
	parent->childs[parent->children] = child;
	parent->children++;
	return SMD_ATTR_LINKED;
}

static size_t smd_attr_ser_json_str(char * buff, const char * str){
	//const char * cur = str;
	//while(*cur != 0){
	//	printf("STR: %d %c\n", cur - str, *cur);
	//	cur++;
	//}
	char c;
	char * buff_p = buff;
	*buff = '"';
	buff++;
	while((c = *str) != 0){
		switch(c){
			case('\b'): {
				*buff = '\\';
				buff++;
			  *buff = 'b';
			  buff++; str++;
			  break;
			}case('\f'): {
				*buff = '\\';
				buff++;
			  *buff = 'f';
			  buff++; str++;
			  break;
			}case('\n'): {
				*buff = '\\';
				buff++;
			  *buff = 'n';
			  buff++; str++;
			  break;
			}case('\r'): {
				*buff = '\\';
				buff++;
			  *buff = 'r';
			  buff++; str++;
			  break;
			}case('\t'): {
				*buff = '\\';
				buff++;
			  *buff = 't';
			  buff++; str++;
			  break;
			}case('\"'): {
				*buff = '\\';
				buff++;
			  *buff = '"';
			  buff++; str++;
			  break;
			}case('\\'):{
				*buff = '\\';
				buff++;
			  *buff = '\\';
			  buff++; str++;
			  break;
			}
			default:
				*buff = *str;
				str++;
				buff++;
		}
	}
	*buff = '"';
	buff++;
	return buff - buff_p;
}

static size_t smd_attr_ser_json_i(char * buff, smd_attr_t * attr);

static size_t smd_attr_ser_json_val(char * buff, void * val, smd_dtype_t * t){
	switch(t->type){
			case(SMD_TYPE_DTYPE):
				buff += sprintf(buff, "\"");
				int count = smd_type_ser(buff, *(smd_dtype_t**) val);
				buff += sprintf(buff + count -1, "\"");
				return count + 1;
			case(SMD_TYPE_EMPTY):
				return sprintf(buff, "null");
			case(SMD_TYPE_INT8):
				return sprintf(buff, "%d", *(int8_t*) val);
			case(SMD_TYPE_INT16):
				return sprintf(buff, "%d", *(int16_t*) val);
			case(SMD_TYPE_INT32):
				return sprintf(buff, "%d", *(int32_t*) val);
			case(SMD_TYPE_INT64):
				return sprintf(buff, "%ld", *(int64_t*) val);
			case(SMD_TYPE_UINT8):
				return sprintf(buff, "%u", *(uint8_t*) val);
			case(SMD_TYPE_UINT16):
				return sprintf(buff, "%u", *(uint16_t*) val);
			case(SMD_TYPE_UINT32):
				return sprintf(buff, "%u", *(uint32_t*) val);
			case(SMD_TYPE_UINT64):
				return sprintf(buff, "%lu", *(int64_t*) val);
			case(SMD_TYPE_FLOAT):
				return sprintf(buff, "%.8e", (double)*(float*) val);
			case(SMD_TYPE_DOUBLE):
				return sprintf(buff, "%.16e", *(double*) val);
			case(SMD_TYPE_CHAR):{
				char c = *(char*) val;
				switch(c){
					case('\b'): {
						return sprintf(buff, "\"\\b\"");
					}case('\f'): {
						return sprintf(buff, "\"\\f\"");
					}case('\n'): {
						return sprintf(buff, "\"\\n\"");
					}case('\r'): {
						return sprintf(buff, "\"\\r\"");
					}case('\t'): {
						return sprintf(buff, "\"\\t\"");
					}case('\"'): {
						return sprintf(buff, "\"\\\"\"");
					}case('\\'):{
						return sprintf(buff, "\"\\\\\"");
					}
					default:
						return sprintf(buff, "\"%c\"", c);
				}
			}case(SMD_TYPE_STRING):{
				return smd_attr_ser_json_str(buff, *(char**) val);
			}case(SMD_TYPE_EXTENT):{
				smd_dtype_extent_t * d = & t->specifier.u.ext;
				return smd_attr_ser_json_val(buff, val, d->base);
			}case(SMD_TYPE_STRUCT):{
				char * buff_p = buff;
				smd_dtype_struct_t * d = & t->specifier.u.str;
				buff += sprintf(buff, "{");
				char * val_pos = val;
				buff += smd_attr_ser_json_str(buff, d->names[0]);
				buff += sprintf(buff, ":");
				buff += smd_attr_ser_json_val(buff, val_pos, d->types[0]);
				val_pos += d->types[0]->size;
				for(int i=1; i < d->size; i++){
					buff += sprintf(buff, ",");
					buff += smd_attr_ser_json_str(buff, d->names[i]);
					buff += sprintf(buff, ":");
					buff += smd_attr_ser_json_val(buff, val_pos, d->types[i]);
					val_pos += d->types[i]->size;
				}
				buff += sprintf(buff, "}");
				return buff - buff_p;
			}case(SMD_TYPE_ARRAY):{
				char * buff_p = buff;
				char * val_pos = val;
				smd_dtype_array_t * d = & t->specifier.u.arr;
				buff += sprintf(buff, "[");
				if( d->count > 0 ){
					buff += smd_attr_ser_json_val(buff, val_pos, d->base);
					val_pos += d->base->size;
					for(uint64_t i=1; i < d->count; i++){
						buff += sprintf(buff, ",");
						buff += smd_attr_ser_json_val(buff, val_pos, d->base);
						val_pos += d->base->size;
					}
				}
				buff += sprintf(buff, "]");
				return buff - buff_p;
			}
		default:
			assert(0 && "SMD cannot serialize unknown type");
	}
}

static size_t smd_attr_ser_json_i(char * buff, smd_attr_t * attr){
	char * buff_p = buff;
	//buff += sprintf(buff, "{");
	buff += smd_attr_ser_json_str(buff, attr->name);
	buff += sprintf(buff, ":{\"type\":\"");
	buff += smd_type_ser_i(buff, attr->type);
	buff += sprintf(buff, "\"");

	buff += sprintf(buff, ",\"data\":");
	if(use_type_ptr(attr->type)){
		buff += smd_attr_ser_json_val(buff, (char*) & attr->value, attr->type);
	}else{
		buff += smd_attr_ser_json_val(buff, attr->value, attr->type);
	}
	if(attr->children){
		buff += sprintf(buff, ",\"childs\":{");
		buff += smd_attr_ser_json_i(buff, attr->childs[0]);
		for(unsigned int i=1; i < attr->children; i++){
			buff += sprintf(buff, ",");
			buff += smd_attr_ser_json_i(buff, attr->childs[i]);
		}
		buff += sprintf(buff, "}");
	}
	buff += sprintf(buff, "}");
	//buff += sprintf(buff, "}");
	return buff - buff_p;
}

size_t smd_attr_ser_json(char * buff, smd_attr_t * attr){
	assert(attr != NULL);
	size_t size = smd_attr_ser_json_i(buff, attr);
	buff[size] = 0;
	return size + 1;
}

static char * smd_attr_string_from_json(char * out, char * str){
	if(*str != '\"') return NULL;
	str++;
	// parse the JSON encoded string
	while(*str != '\"' && *str != 0){
		if(*str == '\\'){
			// escape character
			str++;
			switch(*str){
				case('b'):
					*out = '\b';
					break;
				case('f'):
					*out = '\f';
					break;
				case('n'):
					*out = '\n';
					break;
				case('r'):
					*out = '\r';
					break;
				case('t'):
					*out = '\t';
					break;
				case('\"'):
					*out = '\"';
					break;
				case('\\'):
					*out = '\\';
					break;
				default: // invalid!
					return NULL;
			}
			str++;
			out++;
			continue;
		}
		*out = *str;
		out++;
		str++;
	}

	if(*str != '\"') return NULL;
	str++;
	*out = 0;
	return str;
}

/*
 * Create a packed attribute value from the JSON
 */
static char * smd_attr_val_from_json(char * val, smd_dtype_t * t, char * str){
	int c;
	switch(t->type){
			case(SMD_TYPE_DTYPE):{
				if(*str != '"') return str;
				str++;
				char * pos = str;
				for(; *pos != '\"'; pos++);
				*pos = 0;
				smd_dtype_t * dtype = smd_type_from_ser(str);
				*(smd_dtype_t**) val = dtype;

				*pos = '\"';
				return pos + 1;
			}case(SMD_TYPE_EMPTY):{
				if(strncmp("null", str, 4) != 0) return NULL;
				return str + 4;
			}case(SMD_TYPE_UINT64):{
				uint64_t v;
				sscanf(str, "%lu%n", &v, &c);
				smd_attr_copy_val_to_internal((char*) val, t, &v);
				return str + c;
			}case(SMD_TYPE_INT64):{
				int64_t v;
				sscanf(str, "%ld%n", &v, &c);
				smd_attr_copy_val_to_internal((char*) val, t, &v);
				return str + c;
			}case(SMD_TYPE_INT8):{
				int v;
				sscanf(str, "%d%n", &v, &c);
				smd_attr_copy_val_to_internal((char*) val, t, &v);
				return str + c;
			}case(SMD_TYPE_INT16):{
				int v;
				sscanf(str, "%d%n", &v, &c);
				smd_attr_copy_val_to_internal((char*) val, t, &v);
				return str + c;
			}case(SMD_TYPE_UINT8):{
				unsigned v;
				sscanf(str, "%u%n", &v, &c);
				smd_attr_copy_val_to_internal((char*) val, t, &v);
				return str + c;
			}case(SMD_TYPE_UINT16):{
				unsigned v;
				sscanf(str, "%u%n", &v, &c);
				smd_attr_copy_val_to_internal((char*) val, t, &v);
				return str + c;
			}case(SMD_TYPE_UINT32):{
				unsigned v;
				sscanf(str, "%u%n", &v, &c);
				smd_attr_copy_val_to_internal((char*) val, t, &v);
				return str + c;
			}case(SMD_TYPE_INT32):{
				int v;
				sscanf(str, "%d%n", &v, &c);
				smd_attr_copy_val_to_internal((char*) val, t, &v);
				return str + c;
			}case(SMD_TYPE_FLOAT):{
				float v;
				sscanf(str, "%e%n", &v, &c);
				smd_attr_copy_val_to_internal((char*) val, t, & v);
				return str + c;
			}case(SMD_TYPE_DOUBLE):{
				double v;
				sscanf(str, "%le%n", &v, &c);
				smd_attr_copy_val_to_internal((char*) val, t, & v);
				return str + c;
			}case(SMD_TYPE_CHAR):{
				char buff[4096];
				str = smd_attr_string_from_json(buff, str);
				if(buff[1] != 0) return NULL;
				char * c = (char*) val;
				*c = buff[0];
				return str;
			}case(SMD_TYPE_STRING):{
				char buff[4096];
				str = smd_attr_string_from_json(buff, str);
				*(char**)val = strdup(buff);
				return str;
			}case(SMD_TYPE_EXTENT):{
				smd_dtype_extent_t * d = & t->specifier.u.ext;
				return smd_attr_val_from_json(val, d->base, str);
			}case(SMD_TYPE_STRUCT):{
				char * out_pos = (char*) val;
				smd_dtype_struct_t * d = & t->specifier.u.str;
				if(*str != '{') return NULL;
				str++;
				int s;
				for(int i=0; i < d->size; i++){
					if(i > 0){
						if(*str != ',') return NULL;
						str++;
					}
					if(*str != '"') return NULL;
					str++;
					s = strlen(d->names[i]);
					if(strncmp(str, d->names[i], s) != 0) return NULL;
					str += s;
					if(*str != '"') return NULL;
					str++;
					if(*str != ':') return NULL;
					str++;
					str = smd_attr_val_from_json(out_pos, d->types[i], str);
					out_pos += d->types[i]->size;
				}
				if(*str != '}') return NULL;
				str++;
				return str;
			}case(SMD_TYPE_ARRAY):{
				smd_dtype_array_t * d = & t->specifier.u.arr;
				char * out_pos = (char*) val;
				if(*str != '[') return NULL;
				str++;
				if( d->count > 0 ){
					for(uint64_t i=0; i < d->count; i++){
						if(i > 0){
							if(*str != ',') return NULL;
							str++;
						}
						str = smd_attr_val_from_json(out_pos, d->base, str);
						out_pos += d->base->size;
					}
				}
				if(*str != ']') return NULL;
				str++;
				return str;
			}
		default:
			assert(0 && "SMD cannot convert unknown type from json");
	}

	return str;
}

char * smd_attr_create_from_json_i(char * str, smd_attr_t ** attr_out, size_t size){
	// TODO fix overflow
	assert(str != NULL);
	assert(attr_out != NULL);
	//printf("%d: \"%s\"\n", __LINE__, str);

	char aname[4096];
	str = smd_attr_string_from_json(aname, str);
	if(str == NULL) return NULL;
	if(*str != ':') return NULL;
	str++;
	if(*str != '{') return NULL;
	str++;
	if(strncmp(str, "\"type\":\"", 8) != 0) return NULL;
	str += 8;
	smd_dtype_t * type = smd_type_from_ser_i(& str);
	if(type == NULL) return NULL;

	if(strncmp(str, "\",\"data\":", 9) != 0){
		smd_type_destroy(type);
		return NULL;
	}
	str +=9;

	smd_attr_t * attr;
	attr = smd_attr_new(aname, type, NULL, 0);

	void * val;
	if(use_type_ptr(attr->type)){
		str = smd_attr_val_from_json((char*) & val, type, str);
	}else{
		smd_attr_alloc(& val, type);
		str = smd_attr_val_from_json(val, type, str);
	}
	attr->value = val;

	*attr_out = attr;
	//printf("%d: \"%s\"\n", __LINE__, str);
	if(*str == ','){
		str++;
		// have children
		if(strncmp(str, "\"childs\":{", 10) != 0) {
			smd_type_destroy(type);
			return NULL;
		}
		str += 10;

		while(*str != '}'){
			smd_attr_t * child;
			str = smd_attr_create_from_json_i(str, & child, size);
			smd_attr_link(attr, child, 0);
			if(*str == ',') str++;
		}
		str++;
	}
	if(*str != '}'){
		smd_type_destroy(type);
		return NULL;
	}
	str++;

	return str;
}

smd_attr_t * smd_attr_create_from_json(char * str, size_t length){
	if(length == 0){
		return NULL;
	}
	smd_attr_t * attr;
	smd_attr_create_from_json_i(str, & attr, length);
	return attr;
}

void smd_iterate(smd_attr_t * attr, void (*iter)(int id, const char*name)){
	iter(attr->id, attr->name);
	for(unsigned int i=0; i < attr->children; i++){
		smd_iterate(attr->childs[i], iter);
	}
}

void smd_attr_destroy(smd_attr_t * attr){
	if(attr->childs){
		for(unsigned int i=0; i < attr->children; i++){
			smd_attr_destroy(attr->childs[i]);
		}
		free(attr->childs);
	}
	smd_attr_free_value(attr->value, attr->type);
	free((void*) attr->name);
	free(attr);
}

void * smd_attr_get_value(smd_attr_t * attr){
	return attr->value;
}

const char * smd_attr_get_name(smd_attr_t * attr){
	return attr->name;
}

void smd_attr_copy_value(smd_attr_t * attr, void * out_val){
	assert(attr != NULL);
	if(use_type_ptr(attr->type)){
		smd_attr_copy_val_to_external(out_val, attr->type, (char*) & attr->value);
	}else{
		smd_attr_copy_val_to_external(out_val, attr->type, attr->value);
	}
}


int    smd_attr_count    (const smd_attr_t * attr){
  return attr->children;
}

smd_attr_t * smd_attr_get_child  (const smd_attr_t * attr, unsigned int child){
  assert(attr->children > child);
  return attr->childs[child];
}
