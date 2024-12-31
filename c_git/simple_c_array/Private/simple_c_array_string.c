#define _CRT_SECURE_NO_WARNINGS
#include "../Public/simple_c_array_string.h"
#include <malloc.h>
#include <memory.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

void init_c_string(simple_c_string* c_array)
{
	assert(c_array);
	c_array->size = 0;
	c_array->data = NULL;
}

void destroy_c_string(simple_c_string* c_array)
{
	assert(c_array);
	free(c_array->data);
}

void add_c_string(const char *in_data, simple_c_string* c_array)
{
	assert(c_array);
	
	int cpy_index = c_array->size;
	c_array->size++;
	c_array->data = realloc(c_array->data, sizeof(str_node) * c_array->size);

	strcpy(c_array->data[cpy_index].data, in_data);
}

void print_c_string(simple_c_string* c_array)
{
	assert(c_array);
	for (int i = 0; i < c_array->size; i++) {
		printf("%s \r\n", c_array->data[i].data);
	}
}
