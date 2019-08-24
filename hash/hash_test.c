#include "hash.c"
#include <assert.h>
#include <stdio.h>

int main()
{
	char *str = "HoangKhoi";
	assert(4750844311371674506 == sdbm(str));
	assert(249846319336841277 == djb2(str));

	return 0;
}
