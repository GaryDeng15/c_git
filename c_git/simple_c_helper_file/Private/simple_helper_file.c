#define _CRT_SECURE_NO_WARNINGS
#include "../Public/simple_helper_file.h"
#include <stdio.h>
#include <io.h>

int copy_file(const char* file_src, const char* file_dest)
{
    int result = -1;
    char buffer[256] = { 0 };
    int file_size = 0;
    FILE* file_src_ptr = NULL;
    FILE* file_dest_ptr = NULL;

    if ((file_src_ptr = fopen(file_src, "rb")) != NULL) {
        if ((file_dest_ptr = fopen(file_dest, "wb")) != NULL) {
            while ((file_size = fread(buffer, sizeof(char), sizeof(buffer), file_src_ptr)) > 0) {
                fwrite(buffer, sizeof(char), file_size, file_dest_ptr);
                memset(buffer, 0, sizeof(buffer));
            }
            result = 0;
        }
    }
    return result;
}

void find_files(char const* in_path, def_c_paths* paths, bool b_recursion)
{
	struct _finddata_t finddata;

	long hfile = 0;
	char tmp_path[8196] = { 0 };
	strcpy(tmp_path, in_path);
	strcat(tmp_path, "\\*");
	if ((hfile = _findfirst(tmp_path, &finddata)) != -1)
	{
		do
		{
			if (finddata.attrib & _A_SUBDIR)
			{
				if (b_recursion)
				{
					if (strcmp(finddata.name, ".") == 0 ||
						strcmp(finddata.name, "..") == 0)
					{
						continue;
					}

					char new_path[8196] = { 0 };
					strcpy(new_path, in_path);
					strcat(new_path, "\\");
					strcat(new_path, finddata.name);

					find_files(new_path, paths, b_recursion);
				}
			}
			else
			{
				strcpy(paths->paths[paths->index], in_path);
				strcat(paths->paths[paths->index], "\\");
				strcat(paths->paths[paths->index++], finddata.name);
			}

		} while (_findnext(hfile, &finddata) == 0);
		_findclose(hfile);
	}
}
