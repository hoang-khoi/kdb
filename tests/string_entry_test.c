#include "../string_entry.c"
#include "../string.c"
#include "../entry.c"
#include "../helper.c"

#include <assert.h>
#include <string.h>

unsigned long hash_func(const char *s)
{
	return *s - '0';
}

int main()
{
	struct entry *e = string_entry_new("3.Name", "Khoi");

	assert(string_equals(entry_get_key(e), "3.Name"));
	assert(string_equals(entry_get_value(e), "Khoi"));

	assert(string_entry_key_equals(e, "3.Name"));
	assert(3 == string_entry_hash(e, hash_func));

	string_entry_free(e);

	return 0;
}
