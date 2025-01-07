#pragma once
#include "Core/simple_c_array_marco.h"

typedef struct {
	char data[256];
}str_node;

SIMPLE_C_STRUCT(simple_c_string, str_node);

/**
 * @brief ³õÊ¼»¯×Ö·û´®ÈÝÆ÷¡£
 * @param c_string_array ×Ö·û´®ÈÝÆ÷
*/
void init_c_string(simple_c_string* c_string_array);

/**
 * @brief Ïú»Ù×Ö·û´®ÈÝÆ÷¡£
 * @param c_string_array ×Ö·û´®ÈÝÆ÷
*/
void destroy_c_string(simple_c_string* c_string_array);

/**
 * @brief Ìí¼ÓÒ»¸ö×Ö·û´®µ½ÈÝÆ÷¡£
 * @param in_data Ìí¼Ó×Ö·û´®
 * @param c_string_array ×Ö·û´®ÈÝÆ÷
*/
void add_c_string(const char* in_data, simple_c_string* c_string_array);

/**
 * @brief ´òÓ¡×Ö·û´®ÈÝÆ÷Ã¿¸öÔªËØµ½¿ØÖÆÌ¨¡£
 * @param c_string_array ×Ö·û´®ÈÝÆ÷
*/
void print_c_string(simple_c_string* c_string_array);

/**
 * @brief »ñÈ¡Ö¸¶¨Ë÷ÒýµÄ×Ö·û´®
 * @param index Ö¸¶¨µÄË÷Òý
 * @param c_string_array ×Ö·û´®ÈÝÆ÷
 * @return Ö¸¶¨Ë÷ÒýµÄ×Ö·û´®
*/
char* get_str(int index, simple_c_string* c_string_array);
