#include <stdio.h>
#include "simple_c_array/Public/simple_c_array.h"

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

	system("pause");
	exit(0);
}