#define _CRT_SECURE_NO_WARNINGS
#include "../Public/simple_string_algorithm.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
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

void replace_char_inline(char* str, const char sub_char_a, const char sub_char_b)
{
	int index = find_string(str, &sub_char_a);
	if (index != INDEX_NONE)
	{
		str[index] = sub_char_b;
		replace_char_inline(str, sub_char_a, sub_char_b);
	}
}

int get_printf(char* buf, char* format, ...)
{
	va_list param_list;
	va_start(param_list, format);
	char param_char = *format++;

	for (int i = 0; param_char != '\0'; i++)
	{
		if (param_char != '\%' && *(format - 1) != '\%')
		{
			buf[i] = param_char;
		}
		else
		{
			param_char = *format++;
			switch (param_char)
			{
			case 'c':
			case 'C':
			{
				buf[i] = va_arg(param_list, char);
				break;
			}
			case 's':
			case 'S':
			{
				char* p = va_arg(param_list, char*);
				int len = strlen(p);
				for (int j = 0; j < len;)
				{
					buf[i++] = p[j++];
				}
				i--;

				break;
			}
			case 'd':
			case 'D':
			case 'i':
			case 'I':
			{
				int new_int = va_arg(param_list, int);
				char buf_int[8] = { 0 };
				char* p = itoa(new_int, buf_int, 10);
				int len = strlen(p);
				for (int j = 0; j < len;)
				{
					buf[i++] = p[j++];
				}
				i--;
				break;
			}
			}
		}

		param_char = *format++;
	}

	return strlen(buf) + 1;
}
