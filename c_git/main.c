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
 * @brief .git[.garygit]文件路径
*/
char git_path[MAX_PATH] = { 0 };

/**
 * @brief 日志文件路径
*/
char git_log_path[MAX_PATH] = { 0 };

/**
 * @brief git远端路径
*/
char git_remote_origin[MAX_PATH] = { 0 };

/**
 * @brief git用户信息
*/
typedef struct GitUser {
	/**
	* @brief git账户名
	*/
	char account[MAX_PATH];

	/**
	 * @brief git密码
	*/
	char password[MAX_PATH];

	/**
	 * @brief git邮箱
	*/
	char email[MAX_PATH];
}GitUser;

GitUser user;

/**
 * @brief 日志信息类别
*/
typedef enum LogLevel {
	GIT_LOG,
	GIT_SUCCESS,
	GIT_WARNING,
	GIT_ERROR
};


/**
 * @brief git本地配置文件路径
*/
char git_local_config_path[] = "E:\\local_git\\";

/**
 * @brief git本地配置文件名字
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
 * @param log_level 日志类别
 * @param log_content 打印日志内容
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
 * @brief 初始化引擎
*/
void init_engine() {
	log_log("================== 引擎初始化 ==================");
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
			log_success("当前 git 初始化成功 [%s]", current_git_path);
		}
		else if (strstr(input_buff, "git remote add origin ") != 0) {
			simple_c_string c_string;
			dismantle_string(input_buff, " ", &c_string);
			char * location = get_str(4, &c_string);
			remove_char_end(location, '\n');
			strcpy(git_remote_origin, location);
			log_success("远端的路径设置为 [%s]", git_remote_origin);

			destroy_c_string(&c_string);
		}
		else if (strstr(input_buff, "git --global user.name ") != 0) {
			simple_c_string c_string;
			dismantle_string(input_buff, " ", &c_string);
			char* location = get_str(3, &c_string);
			remove_char_end(location, '\n');
			strcpy(user.account, location);
			log_success("git账号名设置为 %s", user.account);
			destroy_c_string(&c_string);
		}
		else if (strstr(input_buff, "git --global user.password ") != 0) {
			simple_c_string c_string;
			dismantle_string(input_buff, " ", &c_string);
			char* location = get_str(3, &c_string);
			remove_char_end(location, '\n');
			strcpy(user.password, location);
			log_success("git账号密码设置为 %s", user.password);
			destroy_c_string(&c_string);
		}
		else if (strstr(input_buff, "git --global user.email ") != 0) {
			simple_c_string c_string;
			dismantle_string(input_buff, " ", &c_string);
			char* location = get_str(3, &c_string);
			remove_char_end(location, '\n');
			strcpy(user.email, location);
			log_success("git账号邮箱设置为 %s", user.email);
			destroy_c_string(&c_string);
		}
		else if (strstr(input_buff, "ssh-keygen -t rsa -C ") != 0) {
			// OpenSSL RSA加密，上传公钥到git，加密数据，解密数据用私钥
			/*simple_c_string c_string;
			dismantle_string(input_buff, " ", &c_string);
			char* location = get_str(3, &c_string);
			remove_char_end(location, '\n');
			strcpy(user.email, location);
			char log_content[256] = "git账号邮箱设置为：";
			strcat(log_content, user.email);
			log_write(log_content);

			destroy_c_string(&c_string);*/
		}
		else if (strstr(input_buff, "git clone") != 0) {
			simple_c_string c_string;
			dismantle_string(input_buff, " ", &c_string);
			char* clone_path = get_str(2, &c_string);
			remove_char_end(clone_path, '\n');

			if (strstr(clone_path, ".") != 0) {

			}
			else {
				log_error("%s 当前路径非法，至少需要文件名加后缀", clone_path);
			}

			char current_path[MAX_PATH] = { 0 };
			_getcwd(current_path, MAX_PATH);



			simple_c_string clone_path_break;
			if (strstr(clone_path, "\\") != 0) {
				dismantle_string(clone_path, "\\", &clone_path_break);
			}
			else if (strstr(clone_path, "/") != 0) {
				dismantle_string(clone_path, "/", &clone_path_break);
			}
			else {
				log_error("%s 无效，非标准路径", clone_path);
				break;
			}

			char* clone_file_name = get_str(clone_path_break.size, &c_string);
			remove_char_end(clone_file_name, '\n');

			char buff_local_path[MAX_PATH] = { 0 };
			get_printf(buff_local_path, "%s\\%s\\", current_path, clone_file_name);

			def_c_paths file_paths;
			find_files(clone_path, &file_paths, true);
			for (int i = 0; i < file_paths.index; i++) {
				char temp_buff[MAX_PATH] = { 0 };
				strcpy(temp_buff, file_paths.paths[i]);
				remove_string_start(temp_buff, buff_local_path);
				strcat(buff_local_path, temp_buff);
				if (!copy_file(file_paths.paths[i], buff_local_path)) {
					log_log("将 %s 路径下拉取到 %s 成功", file_paths.paths[i], buff_local_path);
				}
				else {
					log_error("将 %s 路径下拉取到 %s 失败", file_paths.paths[i], buff_local_path);
				}
			}

			destroy_c_string(&c_string);
			destroy_c_string(&clone_path_break);
		}
		else if (strstr(input_buff, "git --help") != 0) {
			log_log("git init\t 初始化");
			log_log("git remote add origin\t 设置远端路径");
			log_log("git --global user.name\t 设置用户名");
			log_log("git --global user.password\t 设置密码");
			log_log("git --help \t 帮助手册");
		}
		else {
			log_error("没有该指令 %s", input_buff);
			log_warning("或许你可以通过 git --help 查看相关命令");
		}
	}
}

/**
 * @brief 退出引擎
*/
void exit_engine(){
	log_success("当前 git 退出成功");
	log_log("================== 退出引擎 ==================\r\n");
}

int main() {

	engine_loop();

	exit_engine();

	system("pause");
	exit(0);
}