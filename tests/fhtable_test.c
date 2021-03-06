#include "../fhtable.c"

#include "../list.c"
#include "../string.c"
#include "../entry.c"
#include "../string_entry.c"
#include "../list_string_entry.c"
#include "../helper.c"

#include <assert.h>

/*
 * Mock hash function for a string. Returns the value of first character.
 */
unsigned long hash(const char *str)
{
	return *str - '0';
}

void test_general_functionalities()
{
	int i;
	struct fhtable *ht = fhtable_new(8, 0.75, hash);
	char *keys[6] = {"0", "1", "7", "3", "4", "6"};
	char *values[6] = {
		"0.Hoang",
		"1.Khoi",
		"7.Dep",
		"3.Trai",
		"4.Vai",
		"6.Chuong"
	};

	assert(fhtable_is_empty(ht));

	assert(8 == fhtable_capacity(ht));
	assert(0 == fhtable_size(ht));


	for (i = 0; i < 6; ++i)
		assert(fhtable_set(ht, keys[i], values[i]));

	assert(!fhtable_set(ht, "Denied", "How sad"));

	for (i = 0; i < 6; ++i) {
		struct list *chain = ht->slots[*keys[i] - '0'];
		struct entry *e = list_string_entry_find(chain, keys[i]);
		assert(string_entry_key_equals(e, keys[i]));

	}

	for (i = 0; i < 6; ++i) {
		struct string *value_string = fhtable_get(ht, keys[i]);
		assert(string_equals(value_string, values[i]));
	}

	assert(!fhtable_get(ht, "Denied"));
	assert(6 == fhtable_size(ht));

	fhtable_free(ht);
}

void test_fhtable_move()
{
	struct fhtable *src = fhtable_new(8, 0.75, hash);
	struct fhtable *dest = fhtable_new(16, 0.75, hash);

	fhtable_set(src, "8. Key 1", "Value 1");
	fhtable_set(src, "8. Key 2", "Value 2");
	fhtable_set(src, "9. Key 1", "Value 3");
	fhtable_set(src, "9. Key 2", "Value 4");

	fhtable_move(dest, src, 0);
	fhtable_move(dest, src, 1);

	assert(0 == fhtable_size(src));
	assert(4 == fhtable_size(dest));

	assert(!fhtable_get(src, "8. Key 1"));
	assert(!fhtable_get(src, "8. Key 2"));
	assert(!fhtable_get(src, "9. Key 1"));
	assert(!fhtable_get(src, "9. Key 2"));

	assert(string_equals(fhtable_get(dest, "8. Key 1"), "Value 1"));
	assert(string_equals(fhtable_get(dest, "8. Key 2"), "Value 2"));
	assert(string_equals(fhtable_get(dest, "9. Key 1"), "Value 3"));
	assert(string_equals(fhtable_get(dest, "9. Key 2"), "Value 4"));

	fhtable_free(src);
	fhtable_free(dest);
}

int main()
{
	test_general_functionalities();
	test_fhtable_move();

	return 0;
}
