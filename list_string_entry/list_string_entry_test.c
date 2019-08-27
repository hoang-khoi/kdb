#include "list_string_entry.c"
#include "../list/list.c"
#include "../string/string.c"
#include "../entry/entry.c"
#include "../string_entry/string_entry.c"

#include <assert.h>

unsigned long hash(const char *s)
{
	return 64;
}

int main()
{
	struct list *l = list_new();
	struct entry *tmp_entry;

	list_string_entry_add(l, "Name", "Khoi", hash);
	list_string_entry_add(l, "Age", "24", hash);
	list_string_entry_add(l, "Title", "Memelord", hash);

	// Expect to found entry with key: Name
	tmp_entry = list_string_entry_find(l, "Name");
	assert(string_entry_key_equals(tmp_entry, "Name"));

	// Do not expect to found entry with key: Name
	tmp_entry = list_string_entry_find(l, "age");
	assert(!tmp_entry);

	// Deletes an existing entry
	list_string_entry_del(l, "Name");
	tmp_entry = list_string_entry_find(l, "Name");
	assert(!tmp_entry);

	// Attempt to delete an entry that does not exist
	list_string_entry_del(l, "age");

	// Check the size
	assert(2 == list_size(l));

	list_string_entry_free(l);
}
