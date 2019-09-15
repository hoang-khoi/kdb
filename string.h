#ifndef STRING_H
#define STRING_H

/*
 * String that is aware of its length.
 */

struct string {
	unsigned long length;
	char *buffer;
};

/*
 * Creates a new string from buffer.
 */
struct string *string_new(const char *buffer);
/*
 * Release string's memory.
 */
void string_free(struct string *str);
/*
 * Returns C-style string buffer.
 */
char *string_get_buffer(const struct string *str);
/*
 * Gets string's length.
 */
unsigned long string_length(const struct string *str);
/*
 * Returns 1 if strings are equal to a buffer, 0 otherwise.
 */
int string_equals(const struct string *s, const char *buffer);
/*
 * Returns hash value from a hash algorithm.
 */
unsigned long string_hash(const struct string *s,
			  unsigned long (*hash_func)(const char*));
/*
 * Dumps string to stdout for debugging.
 */
void string_dump(const struct string *s, int level);

#endif
