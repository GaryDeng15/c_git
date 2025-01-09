#define _CRT_SECURE_NO_WARNINGS

#include "simple_c_array/simple_c_array.h"
#include "simple_c_string_algorithm/simple_c_string_algorithm.h"
#include "simple_c_helper_file/simple_c_helper_file.h"
#include "simple_c_windows/simple_c_windows.h"
#include "simple_c_array/simple_c_array.h"
#include <stdio.h>
#include <time.h>
#include <io.h>

/**
 * @brief .git[.garygit]�ļ�·��
*/
char git_path[MAX_PATH] = { 0 };

/**
 * @brief ��־�ļ�·��
*/
char git_log_path[MAX_PATH] = { 0 };

/**
 * @brief gitԶ��·��
*/
char git_remote_origin[MAX_PATH] = { 0 };

/**
 * @brief git�û���Ϣ
*/
typedef struct GitUser {
	/**
	* @brief git�˻���
	*/
	char account[MAX_PATH];

	/**
	 * @brief git����
	*/
	char password[MAX_PATH];

	/**
	 * @brief git����
	*/
	char email[MAX_PATH];
}GitUser;

GitUser user;


/**
 * @brief git���������ļ�·��
*/
char git_local_config_path[] = "E:\\local_git\\";

/**
 * @brief git���������ļ�����
*/
char git_local_config_name[MAX_PATH] = { 0 };

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
 * @brief ��ȡ��ǰʱ���ַ���
 * @return ��ǰʱ���ַ���
*/
char* get_current_time() {
	time_t current;
	time(&current);
	return ctime(&current);
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
 * @brief ��ʼ������
*/
void init_engine() {
	log_write("================== �����ʼ�� ==================\r\n");
	char * current_git_path = get_git_path();
	char* current_log_path = get_log_path();

	char temp_config[MAX_PATH] = { 0 };
	_mkdir(git_local_config_path);
	strcpy(temp_config, git_local_config_path);
	strcat(temp_config, "git_config.ini");
	if ((_access(temp_config, 0) == -1)) {
		create_file(temp_config);
	}
	else {
		FILE* git_config = NULL;
		if ((git_config = fopen(temp_config, "r")) != NULL) {
			char config_buff[1024 * 10] = { 0 };
			int file_size = 0;
			if ((file_size = fread(config_buff, sizeof(char), sizeof(config_buff), git_config)) > 0) {
				simple_c_string temp_string;
				dismantle_string(config_buff, "\n", &temp_string);
				for (int i = 0; i < temp_string.size; i++) {
					if (strstr(temp_string.data[i].data, "Account=")) {
						simple_c_string temp;
						dismantle_string(temp_string.data[i].data, "=", &temp);
						char* value = get_str(1, &temp);
						strcpy(user.account, value);
						destroy_c_string(&temp);
					}
					else if (strstr(temp_string.data[i].data, "Password=")) {
						simple_c_string temp;
						dismantle_string(temp_string.data[i].data, "=", &temp);
						char* value = get_str(1, &temp);
						strcpy(user.password, value);
						destroy_c_string(&temp);
					}
					else if (strstr(temp_string.data[i].data, "RemoteOrigin=")) {
						simple_c_string temp;
						dismantle_string(temp_string.data[i].data, "=", &temp);
						char* value = get_str(1, &temp);
						strcpy(git_remote_origin, value);
						destroy_c_string(&temp);
					}
					else if (strstr(temp_string.data[i].data, "Email=")) {
						simple_c_string temp;
						dismantle_string(temp_string.data[i].data, "=", &temp);
						char* value = get_str(1, &temp);
						strcpy(user.email, value);
						destroy_c_string(&temp);
					}
				}
				destroy_c_string(&temp_string);
			}
		}
	}
}

/**
 * @brief ����ѭ��
*/
void engine_loop() {

	char input_buff[1024] = { 0 };
	int is_exit = 0;
	while (!is_exit) {
		/*log_write("��ǰ git ѭ��\r\n");
		log_write("================== ����ѭ�� ==================\r\n");*/
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
			log_write("��ǰ git ��ʼ���ɹ�");
		}
		else if (strstr(input_buff, "git remote add origin ") != 0) {
			simple_c_string c_string;
			dismantle_string(input_buff, " ", &c_string);
			char * location = get_str(4, &c_string);
			remove_char_end(location, '\n');
			strcpy(git_remote_origin, location);
			char log_content[256] = "Զ�˵�·������Ϊ��";
			strcat(log_content, git_remote_origin);
			log_write(log_content);

			destroy_c_string(&c_string);
		}
		else if (strstr(input_buff, "git --global user.name ") != 0) {
			simple_c_string c_string;
			dismantle_string(input_buff, " ", &c_string);
			char* location = get_str(3, &c_string);
			remove_char_end(location, '\n');
			strcpy(user.account, location);
			char log_content[256] = "git�˺�������Ϊ��";
			strcat(log_content, user.account);
			log_write(log_content);

			destroy_c_string(&c_string);
		}
		else if (strstr(input_buff, "git --global user.password ") != 0) {
			simple_c_string c_string;
			dismantle_string(input_buff, " ", &c_string);
			char* location = get_str(3, &c_string);
			remove_char_end(location, '\n');
			strcpy(user.password, location);
			char log_content[256] = "git�˺���������Ϊ��";
			strcat(log_content, user.password);
			log_write(log_content);

			destroy_c_string(&c_string);
		}
		else if (strstr(input_buff, "git --global user.email ") != 0) {
			simple_c_string c_string;
			dismantle_string(input_buff, " ", &c_string);
			char* location = get_str(3, &c_string);
			remove_char_end(location, '\n');
			strcpy(user.email, location);
			char log_content[256] = "git�˺���������Ϊ��";
			strcat(log_content, user.email);
			log_write(log_content);

			destroy_c_string(&c_string);
		}
		else if (strstr(input_buff, "ssh-keygen -t rsa -C ") != 0) {
			// OpenSSL RSA���ܣ��ϴ���Կ��git���������ݣ�����������˽Կ
			/*simple_c_string c_string;
			dismantle_string(input_buff, " ", &c_string);
			char* location = get_str(3, &c_string);
			remove_char_end(location, '\n');
			strcpy(user.email, location);
			char log_content[256] = "git�˺���������Ϊ��";
			strcat(log_content, user.email);
			log_write(log_content);

			destroy_c_string(&c_string);*/
		}
		else {
			char log_content[256] = "û�и�ָ�";
			strcat(log_content, input_buff);
			log_write(log_content);
		}
	}
}

/**
 * @brief �˳�����
*/
void exit_engine(){
	log_write("��ǰ git �˳��ɹ�\r\n");
	log_write("================== �˳����� ==================\r\n");
}

int main() {

	engine_loop();

	exit_engine();

	system("pause");
	exit(0);
}