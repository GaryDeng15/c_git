#pragma once
/**
 * @brief Ѱ�����ַ�����Ŀ���ַ�������λ�á�
 * @param str Ŀ���ַ���
 * @param sub_str ���ַ���
 * @return �ַ�����һ���ַ�������
*/
int find_string(char* str, char const* sub_str);

/**
 * @brief ���������ַ������Ƴ����ַ�����
 * @param str Ŀ���ַ���
 * @param sub_str ���ַ���
*/
void remove_string_start(char* str, char const* sub_str);

/**
 * @brief �Ӵ�β��ʼ�Ƴ��ַ����г��ֵĵ�һ���ַ���
 * @param str �ַ���
 * @param rm_char Ҫ�Ƴ����ַ�
*/
void remove_char_end(char* str, char rm_char);

/**
 * @brief �Ӵ��׿�ʼ�Ƴ��ַ����г��ֵĵ�һ���ַ���
 * @param str �ַ���
 * @param rm_char Ҫ�Ƴ����ַ�
*/
void remove_char_start(char* str, char rm_char);

/**
 * @brief �滻�ַ������ַ�
 * @param str Ŀ���ַ���
 * @param sub_char_a ���滻�ַ�
 * @param sub_char_b �滻�ַ�
*/
void replace_char_inline(char* str, const char sub_char_a, const char sub_char_b);

/**
 * @brief ��ʽ��ƴ���ַ���
 * @param buf ����ַ���
 * @param format ��ʽ�ַ���
 * @param  �ɱ����
 * @return ��������ַ�����size����'\0'��
*/
int get_printf(char* buf, char* format, ...);
