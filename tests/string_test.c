#include "../string.c"
#include "../helper.c"

#include <assert.h>

unsigned long hash(const char *s)
{
	return *s - '0';
}

int main()
{
	struct string *s = string_new("7.HoangKhoi");

	assert(11 == string_length(s));
	assert(string_equals(s, "7.HoangKhoi"));
	assert(7 == string_hash(s, hash));

	string_free(s);

	return 0;
}
