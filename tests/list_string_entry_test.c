#include "../list_string_entry.c"

#include "../list.c"
#include "../string.c"
#include "../entry.c"
#include "../string_entry.c"
#include "../helper.c"

#include <assert.h>

int main()
{
	struct list *l = list_new();
	struct entry *tmp_entry;

	list_add(l, string_entry_new("Name", "Khoi"));
	list_add(l, string_entry_new("Age", "24"));
	list_add(l, string_entry_new("Title", "Memelord"));

	tmp_entry = list_string_entry_find(l, "Name");
	assert(string_entry_key_equals(tmp_entry, "Name"));

	tmp_entry = list_string_entry_find(l, "age");
	assert(!tmp_entry);

	list_string_entry_del(l, "Name");
	tmp_entry = list_string_entry_find(l, "Name");
	assert(!tmp_entry);

	list_string_entry_del(l, "age");
	assert(2 == list_size(l));

	list_string_entry_free(l);

	return 0;
}
