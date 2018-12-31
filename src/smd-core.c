#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <smd-internal.h>


// Native Datatypes ///////////////////////////////////////////////////////////
static size_t smd_sizeof(smd_basic_type_t type) {
	switch (type) {
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

int smd_find_position_by_name(const smd_attr_t * attr, const char * name){
	for(int i=0; i < attr->children; i++){
		if(strcmp(attr->childs[i]->name, name) == 0){
			return i;
		}
	}
	return -1;
}

int smd_find_position_by_id(const smd_attr_t * attr, int id){
	for(int i=0; i < attr->children; i++){
		if(attr->childs[i]->id == id){
			return i;
		}
	}
	return -1;
}

static void smd_attr_copy_val_to_internal(void ** out, smd_dtype_t * dtype, const void * val){
	smd_basic_type_t type = dtype->type;
	switch(type){
			case(SMD_TYPE_INT8):{
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
			}case(SMD_TYPE_STRING):
				*out = strdup((char*) val);
				break;
		default:
			assert(0 && "SMD cannot copy unknown type");
	}
}


static void smd_attr_copy_val_to_external(void ** out, smd_dtype_t * dtype, const void * val){
	smd_basic_type_t type = dtype->type;

	switch(type){
		  case(SMD_TYPE_INT8):{
		    int8_t * p = (int8_t*) & val;
		    *(int8_t*) out = *p;
		    break;
		  }case(SMD_TYPE_INT16):{
		    int16_t * p = (int16_t*) & val;
		    *(int16_t*) out = *p;
		    break;
		  }case(SMD_TYPE_INT32):{
		    int32_t * p = (int32_t*) & val;
		    *(int32_t*) out = *p;
		    break;
		  }case(SMD_TYPE_INT64):{
		    int64_t * p = (int64_t*) & val;
		    *(int64_t*) out = *p;
		    break;
		  }case(SMD_TYPE_UINT8):{
		    uint8_t * p = (uint8_t*) & val;
		    *(uint8_t*) out = *p;
		    break;
		  }case(SMD_TYPE_UINT16):{
		    uint16_t * p = (uint16_t*) & val;
		    *(uint16_t*) out = *p;
		    break;
		  }case(SMD_TYPE_UINT32):{
		    uint32_t * p = (uint32_t*) & val;
		    *(uint32_t*) out = *p;
		    break;
		  }case(SMD_TYPE_UINT64):{
		    uint64_t * p = (uint64_t*) & val;
		    *(uint64_t*) out = *p;
		    break;
		  }case(SMD_TYPE_FLOAT):{
		    float * p = (float*) & val;
		    *(float*) out = *p;
		    break;
		  }case(SMD_TYPE_DOUBLE):{
		    double * p = (double*) & val;
		    *(double*) out = *p;
		    break;
		  }case(SMD_TYPE_CHAR):{
		    char * p = (char*) & val;
		    *(char*) out = *p;
		    break;
		  }case(SMD_TYPE_STRING):
				*out = strdup((char*) val);
				break;
		default:
			assert(0 && "SMD cannot copy unknown type");
	}
}

static void smd_attr_free_value(void * val, smd_dtype_t * dtype){
	smd_basic_type_t type = dtype->type;

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
				break;
			case(SMD_TYPE_STRING):
				free(val);
				break;
		default:
			assert(0 && "SMD cannot free unknown type");
	}
}

smd_attr_t * smd_attr_new(const char* name, smd_dtype_t * type, const void * val, int * out_id){
	static int id = 0;

	smd_attr_t * attr = malloc(sizeof(smd_attr_t));
	assert(attr != NULL);
	memset(attr, 0, sizeof(smd_attr_t));
	attr->id = id;
	attr->value = (void*) val;
	attr->type = type;
	assert(name != NULL);
	assert(name[0] != 0);

	smd_attr_copy_val_to_internal(& attr->value, type, val);

	attr->name = strdup(name);
	if(out_id != NULL){
		*out_id = id;
	}
	id++;
	return attr;
}

void smd_attr_unlink_pos(smd_attr_t * p, int pos){
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
			for(int i=0; i < parent->children; i++){
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

void smd_iterate(smd_attr_t * attr, void (*iter)(int id, const char*name)){
	iter(attr->id, attr->name);
	for(int i=0; i < attr->children; i++){
		smd_iterate(attr->childs[i], iter);
	}
}

void smd_attr_destroy(smd_attr_t * attr){
	if(attr->childs){
		for(int i=0; i < attr->children; i++){
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

void smd_attr_copy_value(smd_attr_t * attr, void ** out_val){
	assert(attr != NULL);
	smd_attr_copy_val_to_external(out_val, attr->type, attr->value);
}


int    smd_attr_count    (const smd_attr_t * attr){
  return attr->children;
}

smd_attr_t * smd_attr_get_child  (const smd_attr_t * attr, int child){
  assert(child < attr->children);
  return attr->childs[child];
}
