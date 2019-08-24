#include "string.c"
#include <assert.h>

int main()
{
	struct string *s = string_new("HoangKhoi");

	// Test data getters
	assert(9 == string_length(s));
	assert(0 == strcmp("HoangKhoi", string_get_buffer(s)));

	string_free(s);
}
