#include <windows.h>

typedef enum {
	SIMPLE_BLACK = 0,				// 黑色		
	SIMPLE_BLUE,					// 蓝色		
	SIMPLE_GREEN,					// 绿色		
	SIMPLE_LIGHT_BLUE,				// 浅绿色	
	SIMPLE_RED,						// 红色		
	SIMPLE_VIOLET,					// 紫色		
	SIMPLE_YELLOW,					// 黄色		
	SIMPLE_WHITE,					// 白色		
	SIMPLE_GREY,					// 灰色
	SIMPLE_PALE_BLUE,				// 淡蓝色
	SIMPLE_PALE_GREEN,				// 淡绿色
	SIMPLE_LIGHT_GREEN,				// 淡浅绿色
	SIMPLE_PALE_RED,				// 淡红色
	SIMPLE_LAVENDER,				// 淡紫色
	SIMPLE_CANARY_YELLOW,			// 淡黄色
	SIMPLE_BRIGHT_WHITE,			// 亮白色
}simple_c_cmd_windows_color;

void set_console_w_color(simple_c_cmd_windows_color font_color, simple_c_cmd_windows_color background_color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, (unsigned short)font_color + (unsigned short)background_color * 0x10);
}