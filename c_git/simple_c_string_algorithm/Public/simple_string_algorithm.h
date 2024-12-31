#pragma once
/**
 * @brief 寻找子字符串在目标字符串出现位置。
 * @param str 目标字符串
 * @param sub_str 子字符串
 * @return 字符串第一个字符的索引
*/
int find_string(char* str, char const* sub_str);

/**
 * @brief 若包含子字符串，移除子字符串。
 * @param str 目标字符串
 * @param sub_str 子字符串
*/
void remove_string_start(char* str, char const* sub_str);

/**
 * @brief 从串尾开始移除字符串中出现的第一个字符。
 * @param str 字符串
 * @param rm_char 要移除的字符
*/
void remove_char_end(char* str, char rm_char);

/**
 * @brief 从串首开始移除字符串中出现的第一个字符。
 * @param str 字符串
 * @param rm_char 要移除的字符
*/
void remove_char_start(char* str, char rm_char);
