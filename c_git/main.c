#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "simple_c_array/simple_c_array.h"
#include "simple_c_string_algorithm/simple_c_string_algorithm.h"
#include "simple_c_helper_file/simple_c_helper_file.h"

/**
 * @brief .git[.garygit]文件路径
*/
char git_path[256] = { 0 };

/**
 * @brief 日志文件路径
*/
char git_log_path[256] = { 0 };

/**
 * @brief 获取当前时间字符串
 * @return 当前时间字符串
*/
char get_current_time() {
	return ctime(__TIME__);
}

/**
 * @brief 获取.git[.garygit]文件路径
 * @return .git[.garygit]文件路径
*/
char* get_git_path() {
	if (git_path[0] == '\0') {
		char temp_path[256] = { 0 };
		strcat(temp_path, ".\\.garygit\\");

		_mkdir(temp_path);

		strcat(temp_path, "git.txt");

		FILE* git_file = NULL;
		if ((git_file = fopen(temp_path, "a+")) != NULL) {
			strcpy(git_path, temp_path);
			fclose(git_file);
		}
	}
	return git_path;
}

/**
 * @brief 获取日志文件路径
 * @return 日志文件路径
*/
char* get_log_path() {
	if (git_log_path[0] == '\0') {
		char temp_path[256] = { 0 };
		strcat(temp_path, ".\\log\\");

		_mkdir(temp_path);

		char *current_time = get_current_time();
		remove_char_end(current_time, '\n');
		remove_char_end(current_time, '\:');

		strcat(temp_path, current_time);
		const char log_file_suffix[] = ".txt";
		strcat(temp_path, log_file_suffix);

		FILE* log_file = NULL;
		if ((log_file = fopen(temp_path, "a+")) != NULL) {
			strcpy(git_log_path, temp_path);
			fclose(log_file);
		}
	}
	return git_log_path;
}

/**
 * @brief 打印日志到日志文件
 * @param log_content 打印日志内容
*/
void log_write(const char* log_content) {
	char* log_path = get_log_path();
	
	FILE* log_file = NULL;
	if ((log_file = fopen(log_path, "a+")) != NULL) {
		char buff[1024] = { 0 };
		char* current_time = get_current_time();
		remove_char_end(current_time, '\n');

		strcpy(buff, "[");
		strcat(buff, current_time);
		strcat(buff, "] ");
		strcat(buff, log_content);
		strcat(buff, "\r\n");
		//fclose()

		printf(buff);
		fprintf(log_file, buff);
		fclose(log_file);
	}
}

/**
 * @brief 初始化引擎
*/
void init_engine() {
	printf("================== 引擎初始化 ==================\r\n");
	char * current_git_path = get_git_path();
	char* current_log_path = get_log_path();
}

/**
 * @brief 引擎循环
*/
void engine_loop() {
	printf("================== 引擎循环 ==================\r\n");

	char input_buff[1024] = { 0 };
	int is_exit = 0;
	while (!is_exit) {
		printf("请输入指令： \r\n");
		fgets(input_buff, sizeof(input_buff), stdin);
		if (strstr(input_buff, "git exit") != 0)
		{
			is_exit = 1;
		}
		else if (strstr(input_buff, "git init") != 0) {
			init_engine();
			char* current_git_path = get_git_path();
			log_write("当前 git 初始化成功！");
		}
		else {
			printf("没有该指令 %s \r\n", input_buff);
			printf("\r\n");
		}
	}
}

/**
 * @brief 退出引擎
*/
void exit_engine(){
	printf("================== 退出引擎 ==================\r\n");
}

int main() {

	char test[] = "fdaggarykl;k\n";
	remove_char_end(test, 'a');
	printf("%s \r\n", test);

	init_engine();

	engine_loop();

	exit_engine();

	system("pause");
	exit(0);
}