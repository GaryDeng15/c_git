#pragma once
#include "Core/simple_c_array_marco.h"

typedef struct {
	char data[256];
}str_node;

SIMPLE_C_STRUCT(simple_c_string, str_node);

void init_c_string(simple_c_string* c_array);

void destroy_c_string(simple_c_string* c_array);

void add_c_string(const char* in_data, simple_c_string* c_array);

void print_c_string(simple_c_string* c_array);
