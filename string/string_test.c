#include "string.c"
#include <assert.h>

int main()
{
	struct string *s = string_new("HoangKhoi");

	// Test internal data
	assert(9 == s->length);
	assert(0 == strcmp("HoangKhoi", s->buffer));

	// Test public APIs
	assert(9 == string_length(s));
	assert(0 == strcmp("HoangKhoi", string_get_buffer(s)));

	string_free(s);
}
