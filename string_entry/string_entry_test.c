#include "string_entry.c"
#include "../string/string.c"
#include "../entry/entry.c"

#include <assert.h>
#include <string.h>

int main()
{
	struct entry *e = string_entry_new("Name", "Khoi", 32);

	assert(string_equals(entry_get_key(e), "Name"));
	assert(string_equals(entry_get_value(e), "Khoi"));

	// Test string_entry_key_equals()
	assert(string_entry_key_equals(e, "Name"));

	string_entry_free(e);
}
