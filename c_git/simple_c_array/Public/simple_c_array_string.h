#pragma once
#include "Core/simple_c_array_marco.h"

typedef struct {
	char data[256];
}str_node;

SIMPLE_C_STRUCT(simple_c_string, str_node);

/**
 * @brief ³õÊ¼»¯×Ö·û´®ÈİÆ÷¡£
 * @param c_string_array ×Ö·û´®ÈİÆ÷
*/
void init_c_string(simple_c_string* c_string_array);

/**
 * @brief Ïú»Ù×Ö·û´®ÈİÆ÷¡£
 * @param c_string_array ×Ö·û´®ÈİÆ÷
*/
void destroy_c_string(simple_c_string* c_string_array);

/**
 * @brief Ìí¼ÓÒ»¸ö×Ö·û´®µ½ÈİÆ÷¡£
 * @param in_data Ìí¼Ó×Ö·û´®
 * @param c_string_array ×Ö·û´®ÈİÆ÷
*/
void add_c_string(const char* in_data, simple_c_string* c_string_array);

/**
 * @brief ´òÓ¡×Ö·û´®ÈİÆ÷Ã¿¸öÔªËØµ½¿ØÖÆÌ¨¡£
 * @param c_string_array ×Ö·û´®ÈİÆ÷
*/
void print_c_string(simple_c_string* c_string_array);
