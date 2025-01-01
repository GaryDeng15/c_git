#define _CRT_SECURE_NO_WARNINGS
#include "../Public/simple_string_algorithm.h"
#include <stdio.h>
#include <string.h>
#define INDEX_NONE -1

int find_string(char* str, char const* sub_str)
{
	int len = strlen(sub_str);
	int index = INDEX_NONE;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (sub_str[0] == str[i])
		{
			int tmp_index = i;
			int l = 1;//第一个是成功
			while (sub_str[l] == str[i + l])
			{
				l++;
			}

			if (len == l)
			{
				index = tmp_index;
				break;
			}
		}
	}

	return index;
}

void remove_string_start(char* str, char const* sub_str)
{
	int index = find_string(str, sub_str);
	if (index != INDEX_NONE)
	{
		strcpy(&str[index], &str[index + strlen(sub_str)]);
	}
}

void remove_char_end(char* str, char rm_char)
{
	int len = strlen(str);

	for (int i = len; i >= 0; i--)
	{
		if (str[i] == rm_char)
		{
			strcpy(&str[i], &str[i + 1]);
		}
	}
}

void remove_char_start(char* str, char rm_char)
{
	int len = strlen(str) + 1;

	//从头开始检查 然后删除对象
	for (int i = 0; i < len; i++)
	{
		if (str[i] == rm_char)
		{
			do
			{
				str[i] = str[i + 1];
				i++;
			} while (str[i + 1] != '\0');
			str[i] = '\0';

			break;
		}
	}
}
