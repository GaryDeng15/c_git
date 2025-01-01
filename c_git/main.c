#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "simple_c_array/simple_c_array.h"
#include "simple_c_string_algorithm/simple_c_string_algorithm.h"
#include "simple_c_helper_file/simple_c_helper_file.h"

/**
 * @brief .git[.garygit]�ļ�·��
*/
char git_path[256] = { 0 };

/**
 * @brief ��־�ļ�·��
*/
char git_log_path[256] = { 0 };

/**
 * @brief ��ȡ��ǰʱ���ַ���
 * @return ��ǰʱ���ַ���
*/
char get_current_time() {
	return ctime(__TIME__);
}

/**
 * @brief ��ȡ.git[.garygit]�ļ�·��
 * @return .git[.garygit]�ļ�·��
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
 * @brief ��ȡ��־�ļ�·��
 * @return ��־�ļ�·��
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
 * @brief ��ӡ��־����־�ļ�
 * @param log_content ��ӡ��־����
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
 * @brief ��ʼ������
*/
void init_engine() {
	printf("================== �����ʼ�� ==================\r\n");
	char * current_git_path = get_git_path();
	char* current_log_path = get_log_path();
}

/**
 * @brief ����ѭ��
*/
void engine_loop() {
	printf("================== ����ѭ�� ==================\r\n");

	char input_buff[1024] = { 0 };
	int is_exit = 0;
	while (!is_exit) {
		printf("������ָ� \r\n");
		fgets(input_buff, sizeof(input_buff), stdin);
		if (strstr(input_buff, "git exit") != 0)
		{
			is_exit = 1;
		}
		else if (strstr(input_buff, "git init") != 0) {
			init_engine();
			char* current_git_path = get_git_path();
			log_write("��ǰ git ��ʼ���ɹ���");
		}
		else {
			printf("û�и�ָ�� %s \r\n", input_buff);
			printf("\r\n");
		}
	}
}

/**
 * @brief �˳�����
*/
void exit_engine(){
	printf("================== �˳����� ==================\r\n");
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