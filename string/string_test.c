#include "string.c"
#include "../formatter/formatter.c"

#include <assert.h>

int main()
{
	struct string *s = string_new("HoangKhoi");

	// Test data getters
	assert(9 == string_length(s));
	assert(0 == strcmp("HoangKhoi", string_get_buffer(s)));

	// Test string_equals
	assert(string_equals(s, "HoangKhoi"));

	string_dump(s, 0);

	string_free(s);
}
