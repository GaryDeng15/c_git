#define _CRT_SECURE_NO_WARNINGS

#include "simple_c_array/simple_c_array.h"
#include "simple_c_string_algorithm/simple_c_string_algorithm.h"
#include "simple_c_helper_file/simple_c_helper_file.h"
#include "simple_c_windows/simple_c_windows.h"
#include "simple_c_array/simple_c_array.h"
#include <stdio.h>
#include <time.h>

/**
 * @brief .git[.garygit]文件路径
*/
char git_path[256] = { 0 };

/**
 * @brief 日志文件路径
*/
char git_log_path[256] = { 0 };

/**
 * @brief git远端路径
*/
char git_remote_origin[256] = { 0 };

// Core

void init_engine();
void engine_loop();
void exit_engine();

// Get

char* get_current_time();
char* get_git_path();
char* get_log_path();
void log_write(const char* log_content);


/**
 * @brief 获取当前时间字符串
 * @return 当前时间字符串
*/
char* get_current_time() {
	time_t current;
	time(&current);
	return ctime(&current);
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

		strcpy(buff, "\r\n[");
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
	log_write("================== 引擎初始化 ==================\r\n");
	char * current_git_path = get_git_path();
	char* current_log_path = get_log_path();
}

/**
 * @brief 引擎循环
*/
void engine_loop() {

	char input_buff[1024] = { 0 };
	int is_exit = 0;
	while (!is_exit) {
		/*log_write("当前 git 循环\r\n");
		log_write("================== 引擎循环 ==================\r\n");*/
		printf("\r\n");
		set_console_w_color(SIMPLE_PALE_GREEN, 0);
		printf("GARY ssh : ");
		set_console_w_color(SIMPLE_LAVENDER, 0);
		printf("WINDOWS64 ");
		set_console_w_color(SIMPLE_CANARY_YELLOW, 0);
		char buf_cwd[MAX_PATH];
		_getcwd(buf_cwd, MAX_PATH);
		printf(" %s \r\n", buf_cwd);
		set_console_w_color(SIMPLE_WHITE, 0);
		printf(" \r\n ");
		printf(" $ ");
		fgets(input_buff, sizeof(input_buff), stdin);
		if (strstr(input_buff, "git exit") != 0)
		{
			is_exit = 1;
		}
		else if (strstr(input_buff, "git init") != 0) {
			init_engine();
			char* current_git_path = get_git_path();
			log_write("当前 git 初始化成功");
		}
		else if (strstr(input_buff, "git remote add origin ") != 0) {
			simple_c_string c_string;
			init_c_string(&c_string);

			char* temp = strtok(input_buff, " ");
			while (temp) {
				if ((temp = strtok(NULL, " ")) != NULL) {
					add_c_string(temp, &c_string);
				}
			}
			char * location = get_str(3, &c_string);
			remove_char_end(location, '\n');
			strcpy(git_remote_origin, location);
			char log_content[256] = "远端的路径设置为：";
			strcat(log_content, git_remote_origin);
			log_write(log_content);

			destroy_c_string(&c_string);
		}
		else {
			char log_content[256] = "没有该指令：";
			strcat(log_content, input_buff);
			log_write(log_content);
		}
	}
}

/**
 * @brief 退出引擎
*/
void exit_engine(){
	log_write("当前 git 退出成功\r\n");
	log_write("================== 退出引擎 ==================\r\n");
}

int main() {

	engine_loop();

	exit_engine();

	system("pause");
	exit(0);
}