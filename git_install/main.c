#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

#define REG_SHELL_DIRECTORY			"*\\Shell\\"
#define REG_BACKGROUND_DIRECTORY	"Directory\\Background\\shell\\"
#define REG_DESKTOP_BACKGROUND		"DesktopBackground\\shell\\"

typedef struct {
	char name[MAX_PATH];
	DWORD type;
	char value[1024];
}RegItem;

typedef struct {
	HKEY key;
	char path[MAX_PATH];
	int item_count;
	RegItem items[1024];
}RegInfo;

void init_reg_info(RegInfo* info);

bool register_info(RegInfo* info);

bool delete_register_info(HKEY key, const char* key_name);

bool delete_register_key(HKEY key, const char* key_name, const char *sub_key_name);

int main(int argc, char* argv[]) {

	const char *commit_type = argv[1];
	const char* path_exe = argv[2];
	const char* path_icon = argv[3];
	const char* name = argv[4];

	char temp_reg_key[MAX_PATH] = { 0 };
	char temp_sub_reg_key[MAX_PATH] = { 0 };
	strcpy(temp_reg_key, REG_BACKGROUND_DIRECTORY);
	strcat(temp_reg_key, name);

	strcpy(temp_sub_reg_key, REG_BACKGROUND_DIRECTORY);
	strcat(temp_sub_reg_key, name);
	strcat(temp_sub_reg_key, "\\command");

	if (strcmp(commit_type, "1") == 0) { // 安装
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
	else if (strcmp(commit_type, "2") == 0) { // 卸载
		if (delete_register_info(HKEY_CLASSES_ROOT, temp_reg_key)) {
			delete_register_key(HKEY_CLASSES_ROOT, REG_BACKGROUND_DIRECTORY, name);
		}
	}

	system("pause");
	return 0;
}

void init_reg_info(RegInfo* info)
{
	info->item_count = 0;
	memset(info->path, 0, sizeof(info->path));
	memset(info->items, 0, sizeof(info->items));
}

bool register_info(RegInfo* info)
{
	HKEY result;
	long result_value = -1;
	if (result_value = RegCreateKeyEx(info->key, info->path, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_CREATE_SUB_KEY | KEY_ALL_ACCESS, NULL, &result, NULL) == ERROR_SUCCESS) {
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
		printf("\n error code RegCreateKeyEx = %i \n", result_value);
	}
	return false;
}

bool delete_register_info(HKEY key, const char *key_name)
{
	HKEY result;
	long result_value = -1;
	DWORD count;
	int error_count = 0;
	if ((result_value = RegOpenKeyEx(result, key_name, 0, KEY_READ, &result)) == ERROR_SUCCESS) {
		if ((result_value = RegQueryInfoKey(result, NULL, NULL, NULL, &count, NULL, NULL, NULL, NULL, NULL, NULL, NULL)) == ERROR_SUCCESS) {
			char sub_key_name[MAX_PATH] = { 0 };
			for (DWORD i = 0; i < count; i++) {
				if ((result_value = RegEnumKey(result, i, sub_key_name, MAX_PATH)) == ERROR_SUCCESS) {
					if ((result_value = RegDeleteKey(result, sub_key_name)) != ERROR_SUCCESS) {
						error_count++;
						printf("\n error %s 该键存在子项，无法删除 \n", sub_key_name);
					}
				}
				else {
					error_count++;
					printf("\n error \n");
				}
			}
		}
		else {
			error_count++;
			printf("\n error \n");
		}
		RegCloseKey(result);

	}
	else {
		error_count++;
		printf("\n error %s 无效 或者 需要管理员权限 \n", key_name);
	}

	if(!error_count)
	{
		return true;
	}
	else {
		return false;
	}
}

bool delete_register_key(HKEY key, const char* key_name, const char* sub_key_name)
{
	HKEY result;
	long value = -1;
	if ((value = RegOpenKeyEx(key, key_name, 0, KEY_READ, &result)) == ERROR_SUCCESS)
	{
		if (value = RegDeleteKey(result, sub_key_name) != ERROR_SUCCESS)
		{
			return true;
		}
	}

	return false;
}
