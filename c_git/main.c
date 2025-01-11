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
 * @brief ��־��Ϣ���
*/
typedef enum LogLevel {
	GIT_LOG,
	GIT_SUCCESS,
	GIT_WARNING,
	GIT_ERROR
};


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

// Log

void log_write(enum LogLevel log_level,const char* log_content, ...);

#define log_log(...) log_write(GIT_LOG, __VA_ARGS__)
#define log_success(...) log_write(GIT_SUCCESS, __VA_ARGS__)
#define log_error(...) log_write(GIT_ERROR, __VA_ARGS__)
#define log_warning(...) log_write(GIT_WARNING, __VA_ARGS__)


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
 * @param log_level ��־���
 * @param log_content ��ӡ��־����
 * @return 
*/
void log_write(enum LogLevel log_level, char* log_content, ...) {
	char log_level_str[64] = {0};

	switch (log_level)
	{
	case GIT_LOG:
		strcpy(log_level_str, "LOG");
		break;
	case GIT_SUCCESS:
		strcpy(log_level_str, "SUCCESS");
		break;
	case GIT_WARNING:
		strcpy(log_level_str, "WARNNING");
		break;
	case GIT_ERROR:
		strcpy(log_level_str, "ERROR");
		break;
	default:
		break;
	}
	

	char* log_path = get_log_path();
	
	FILE* log_file = NULL;
	if ((log_file = fopen(log_path, "a+")) != NULL) {
		char buff[1024] = { 0 };
		ZeroMemory(buff, sizeof(char) * 1024);
		va_list args;
		va_start(args, log_content);
		_vsnprintf_s(buff, 1024 - 1, 1024, log_content, args);
		va_end(args);
		buff[1024 - 1] = 0;

		char* current_time = get_current_time();
		remove_char_end(current_time, '\n');
		char result[1024] = { 0 };
		get_printf(result, "\r\n[%s][%s] %s", current_time, log_level_str, buff);

		switch (log_level)
		{
		case GIT_LOG:
			set_console_w_color(SIMPLE_WHITE, SIMPLE_BLACK);
			printf(result);
			break;
		case GIT_SUCCESS:
			set_console_w_color(SIMPLE_GREEN, SIMPLE_BLACK);
			printf(result);
			break;
		case GIT_WARNING:
			set_console_w_color(SIMPLE_YELLOW, SIMPLE_BLACK);
			printf(result);
			break;
		case GIT_ERROR:
			set_console_w_color(SIMPLE_RED, SIMPLE_BLACK);
			printf(result);
			break;
		default:
			break;
		}
		set_console_w_color(SIMPLE_WHITE, SIMPLE_BLACK);
		fprintf(log_file, result);
		fclose(log_file);
	}
}

/**
 * @brief ��ʼ������
*/
void init_engine() {
	log_log("================== �����ʼ�� ==================");
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
			log_success("��ǰ git ��ʼ���ɹ� [%s]", current_git_path);
		}
		else if (strstr(input_buff, "git remote add origin ") != 0) {
			simple_c_string c_string;
			dismantle_string(input_buff, " ", &c_string);
			char * location = get_str(4, &c_string);
			remove_char_end(location, '\n');
			strcpy(git_remote_origin, location);
			log_success("Զ�˵�·������Ϊ [%s]", git_remote_origin);

			destroy_c_string(&c_string);
		}
		else if (strstr(input_buff, "git --global user.name ") != 0) {
			simple_c_string c_string;
			dismantle_string(input_buff, " ", &c_string);
			char* location = get_str(3, &c_string);
			remove_char_end(location, '\n');
			strcpy(user.account, location);
			log_success("git�˺�������Ϊ %s", user.account);
			destroy_c_string(&c_string);
		}
		else if (strstr(input_buff, "git --global user.password ") != 0) {
			simple_c_string c_string;
			dismantle_string(input_buff, " ", &c_string);
			char* location = get_str(3, &c_string);
			remove_char_end(location, '\n');
			strcpy(user.password, location);
			log_success("git�˺���������Ϊ %s", user.password);
			destroy_c_string(&c_string);
		}
		else if (strstr(input_buff, "git --global user.email ") != 0) {
			simple_c_string c_string;
			dismantle_string(input_buff, " ", &c_string);
			char* location = get_str(3, &c_string);
			remove_char_end(location, '\n');
			strcpy(user.email, location);
			log_success("git�˺���������Ϊ %s", user.email);
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
		else if (strstr(input_buff, "git --help") != 0) {
			log_log("git init\t ��ʼ��");
			log_log("git remote add origin\t ����Զ��·��");
			log_log("git --global user.name\t �����û���");
			log_log("git --global user.password\t ��������");
			log_log("git --help \t �����ֲ�");
		}
		else {
			log_error("û�и�ָ�� %s", input_buff);
			log_warning("���������ͨ�� git --help �鿴�������");
		}
	}
}

/**
 * @brief �˳�����
*/
void exit_engine(){
	log_success("��ǰ git �˳��ɹ�");
	log_log("================== �˳����� ==================\r\n");
}

int main() {

	engine_loop();

	exit_engine();

	system("pause");
	exit(0);
}