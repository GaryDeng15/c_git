#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>

#define REG_SHELL_DIRECTORY			"*\\Shell\\"
#define REG_BACKGROUND_DIRECTORY	"Directory\\Background\\Shell\\"
#define REG_DESKTOP_BACKGROUND		"DesktopBackground\\shell\\"

typedef struct {
	char name[MAX_PATH];
	DWORD type;
	char value[1024];
}RegItem;

typedef struct {
	HKEY key;
	char* path[MAX_PATH];
	int item_count;
	RegItem items[1024];
}RegInfo;

void init_reg_info(RegInfo* info);

bool register_info(RegInfo* info);

int main(int argc, char* argv[]) {
	const char *commit_type = argv[1];
	const char* path_exe = argv[2];
	const char* path_icon = argv[3];
	const char* name = argv[4];

	char temp_reg_key[MAX_PATH] = { 0 };
	char temp_sub_reg_key[MAX_PATH] = { 0 };
	strcpy(temp_reg_key, REG_SHELL_DIRECTORY);
	strcat(temp_reg_key, name);

	strcpy(temp_sub_reg_key, REG_SHELL_DIRECTORY);
	strcat(temp_sub_reg_key, name);
	strcat(temp_sub_reg_key, "\\Command");

	if (strcmp(commit_type, "1")) { // 安装
		RegInfo reg_info;
		init_reg_info(&reg_info);
		strcpy(reg_info.path, temp_reg_key);
		reg_info.key = HKEY_CLASSES_ROOT;
		{
			reg_info.items[reg_info.item_count].type = REG_SZ;
			strcpy(reg_info.items[reg_info.item_count++].value, name);

			reg_info.items[reg_info.item_count].type = REG_SZ;
			strcpy(reg_info.items[reg_info.item_count].name, "icon");
			strcpy(reg_info.items[reg_info.item_count++].value, path_icon);
		}

		if (!register_info(&reg_info)) {
			printf("\n 1 需要管理员权限 \n");
			system("pause");
			return 1;
		}

		init_reg_info(&reg_info);
		strcpy(reg_info.path, temp_sub_reg_key);
		reg_info.key = HKEY_CLASSES_ROOT;
		{
			reg_info.items[reg_info.item_count].type = REG_SZ;
			strcpy(reg_info.items[reg_info.item_count++].value, path_exe);
		}

		if (!register_info(&reg_info)) {
			printf("\n 2 需要管理员权限 \n");
			system("pause");
			return 1;
		}
	}
	else if (strcmp(commit_type, "2")) { // 卸载
		
	}

	

	system("pause");
	return 0;
}

void init_reg_info(RegInfo* info)
{
	info->item_count = 0;
	memset(info->path, 0, sizeof(info));
	memset(info->items, 0, sizeof(info));
}

bool register_info(RegInfo* info)
{
	HKEY result;
	long result_value = -1;
	if (result_value = RegCreateKeyEx(
		info->key,
		info->path,
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_CREATE_SUB_KEY | KEY_ALL_ACCESS,
		NULL,
		&result,
		NULL
		) == ERROR_SUCCESS) {

		for (int i = 0; i < info->item_count; i++) {
			char* temp_name = info->items[i].name[0] == '\0' ? NULL : info->items[i].name;
			if (result_value = RegSetValueEx(
				result,
				temp_name,
				0,
				info->items[i].type,
				info->items[i].value,
				sizeof(info->items[i].value)
				) != ERROR_SUCCESS) {
				printf("\n error code RegSetValueEx = %i \n", result_value);
			}
		}

		RegCloseKey(&result);
		return true;
	}
	else {
		printf("\n error code RegSetValueEx = %i \n", result_value);
	}
	return false;
}
