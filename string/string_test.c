#include "string.c"
#include "../formatter/formatter.c"

#include <assert.h>

unsigned long hash(const char *s)
{
	return *s - '0';
}

int main()
{
	struct string *s = string_new("7.HoangKhoi");

	// Test data getters
	assert(11 == string_length(s));

	// Test string_equals()
	assert(string_equals(s, "7.HoangKhoi"));

	// Test string_hash()
	assert(7 == string_hash(s, hash));

	string_free(s);
}
