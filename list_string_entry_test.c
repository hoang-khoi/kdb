#include "list_string_entry.c"

#include "list.c"
#include "string.c"
#include "entry.c"
#include "string_entry.c"
#include "helper.c"

#include <assert.h>

unsigned long hash(const char *s)
{
	return 64;
}

int main()
{
	struct list *l = list_new();
	struct entry *tmp_entry;

	list_add(l, string_entry_new("Name", "Khoi"));
	list_add(l, string_entry_new("Age", "24"));
	list_add(l, string_entry_new("Title", "Memelord"));

	// Expect to find an entry with key "Name"
	tmp_entry = list_string_entry_find(l, "Name");
	assert(string_entry_key_equals(tmp_entry, "Name"));

	// Do not expect to found entry with key: age
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
