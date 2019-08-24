#include "list_string_entry.c"
#include "../list/list.c"
#include "../string/string.c"
#include "../entry/entry.c"
#include "../string_entry/string_entry.c"

int main()
{
	struct list *l = list_new();
	list_string_entry_add(l, "Name", "Khoi");
	list_string_entry_add(l, "Age", "24");
	list_string_entry_add(l, "Title", "Memelord");

	struct node *it = list_begin(l);

	list_string_entry_free(l);
}
