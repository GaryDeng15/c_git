#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <memory.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define SIMPLE_C_STRUCT(array_name, data_type) \
typedef struct { \
	int size; \
	data_type* data; \
}array_name;


#define SIMPLE_C_ARRAY(array_name, data_type) \
typedef struct { \
	int size; \
	int max_size; \
	data_type* data; \
}array_name; \
void init_##array_name(array_name* c_array) \
{ \
	assert(c_array); \
	c_array->size = 0; \
	c_array->max_size = 1; \
	c_array->data = malloc(sizeof(data_type) * c_array->max_size); \
	memset(c_array->data, 0, c_array->max_size); \
} \
void destroy_##array_name(array_name* c_array) \
{ \
	assert(c_array); \
	free(c_array->data); \
} \
void add_##array_name(data_type in_data, array_name* c_array) \
{ \
	assert(c_array); \
	if (c_array->size >= c_array->max_size) { \
		c_array->max_size += 1; \
		c_array->data = realloc(c_array->data, sizeof(data_type) * c_array->max_size); \
	} \
	c_array->data[c_array->size++] = in_data; \
} 


