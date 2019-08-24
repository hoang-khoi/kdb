#include "string_entry.c"
#include "../string/string.c"
#include "../entry/entry.c"

#include <assert.h>

int main()
{
	struct entry *e = string_entry_new("Name", "Khoi");

	assert(0 == strcmp("Name", string_get_buffer(entry_get_key(e))));
	assert(0 == strcmp("Khoi", string_get_buffer(entry_get_value(e))));

	string_entry_free(e);
}
