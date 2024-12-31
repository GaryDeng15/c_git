#pragma once
#include <stdbool.h>

/** 
* @brief  ��Դ·�������ļ���Ŀ��·����
* @param file_src  Դ·��
* @param file_dest  Ŀ��·��
* @return 0���ɹ���������ʧ��
*/
int copy_file(const char* file_src, const char* file_dest);

/**
 * @brief �����ļ������ṹ�壬��Ҫ�洢�ļ���
*/
typedef struct
{
	int index;
	char paths[30][36];
}def_c_paths;
/** 
* @brief  ����ָ��·���µ������ļ���
* @param in_path  ָ��·��
* @param paths  �����ļ������ṹ�壬��Ҫ�洢�ļ���
* @param b_recursion �Ƿ�ݹ����
*/
void find_files(char const* in_path, def_c_paths* paths, bool b_recursion);