#define _CRT_SECURE_NO_WARNINGS
#include "../Public/simple_helper_file.h"
#include <stdio.h>

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
