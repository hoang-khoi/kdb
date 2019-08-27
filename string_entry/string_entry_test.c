#include "string_entry.c"
#include "../string/string.c"
#include "../entry/entry.c"
#include "../formatter/formatter.c"

#include <assert.h>
#include <string.h>

unsigned long hash(const char *s)
{
	return 16;
}

int main()
{
	struct entry *e = string_entry_new("Name", "Khoi", hash);

	assert(string_equals(entry_get_key(e), "Name"));
	assert(string_equals(entry_get_value(e), "Khoi"));

	// Test string_entry_key_equals()
	assert(string_entry_key_equals(e, "Name"));
	assert(16 == entry_get_hash(e));

	string_entry_dump(e, 0);

	string_entry_free(e);
}
