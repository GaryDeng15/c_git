#pragma once

/** 
* @brief  从源路径复制文件到目标路径。
* @param file_src  源路径
* @param file_dest  目标路径
* @return 0：成功，其他：失败
*/
int copy_file(const char* file_src, const char* file_dest);