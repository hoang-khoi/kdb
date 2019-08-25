#include "list_string_entry.c"
#include "../list/list.c"
#include "../string/string.c"
#include "../entry/entry.c"
#include "../string_entry/string_entry.c"

#include <assert.h>

int main()
{
	struct list *l = list_new();
	struct entry *name;

	list_string_entry_add(l, "Name", "Khoi");
	list_string_entry_add(l, "Age", "24");
	list_string_entry_add(l, "Title", "Memelord");


	name = list_string_entry_find(l, "Name");
	assert(string_entry_key_equals(name, "Name"));

	name = list_string_entry_find(l, "age");
	assert(!name);


	list_string_entry_free(l);
}
