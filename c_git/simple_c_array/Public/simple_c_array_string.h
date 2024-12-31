#pragma once
#include "Core/simple_c_array_marco.h"

typedef struct {
	char data[256];
}str_node;

SIMPLE_C_STRUCT(simple_c_string, str_node);

/**
 * @brief ��ʼ���ַ���������
 * @param c_string_array �ַ�������
*/
void init_c_string(simple_c_string* c_string_array);

/**
 * @brief �����ַ���������
 * @param c_string_array �ַ�������
*/
void destroy_c_string(simple_c_string* c_string_array);

/**
 * @brief ����һ���ַ�����������
 * @param in_data �����ַ���
 * @param c_string_array �ַ�������
*/
void add_c_string(const char* in_data, simple_c_string* c_string_array);

/**
 * @brief ��ӡ�ַ�������ÿ��Ԫ�ص�����̨��
 * @param c_string_array �ַ�������
*/
void print_c_string(simple_c_string* c_string_array);