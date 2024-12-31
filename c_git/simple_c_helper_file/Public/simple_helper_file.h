#pragma once
#include <stdbool.h>

/** 
* @brief  从源路径复制文件到目标路径。
* @param file_src  源路径
* @param file_dest  目标路径
* @return 0：成功，其他：失败
*/
int copy_file(const char* file_src, const char* file_dest);

/**
 * @brief 查找文件辅助结构体，主要存储文件名
*/
typedef struct
{
	int index;
	char paths[30][36];
}def_c_paths;
/** 
* @brief  查找指定路径下的所有文件。
* @param in_path  指定路径
* @param paths  查找文件辅助结构体，主要存储文件名
* @param b_recursion 是否递归查找
*/
void find_files(char const* in_path, def_c_paths* paths, bool b_recursion);