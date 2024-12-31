#include <stdio.h>
#include "simple_c_array/simple_c_array.h"
#include "simple_c_string_algorithm/Public/simple_string_algorithm.h"
#include "simple_c_helper_file/Public/simple_helper_file.h"
int main() {

	simple_c_int int_array;
	init_simple_c_int(&int_array);
	{
		add_simple_c_int(1, &int_array);
		add_simple_c_int(2, &int_array);
		add_simple_c_int(3, &int_array);
	}
	for (int i = 0; i < int_array.size; i++) {
		printf("%d \r\n", int_array.data[i]);
	}

	char str[] = "jkoepgaryeaew";
	char sub_str[] = "gary";
	remove_string_start(&str, &sub_str);
	printf("%s \r\n", str);
	remove_char_start(str, 'e');
	printf("%s \r\n", str);
	remove_char_end(str, 'e');
	printf("%s \r\n", str);

	int result = copy_file(
		"E:\\UnrealProjects\\Learning\\AboutCG\\Renzhai\\c_git\\c_git\\test.txt", 
		"E:\\UnrealProjects\\Learning\\AboutCG\\Renzhai\\c_git\\c_git\\gary.txt");
	printf("%d \r\n", result);

	def_c_paths def_c_paths;
	def_c_paths.index = 0;

	find_files("E:\\Projects", &def_c_paths,true);

	for (int i = 0; i < def_c_paths.index; i++)
	{
		printf("%s \r\n", def_c_paths.paths[i]);
	}

	system("pause");
	exit(0);
}