#ifndef STRING_H
#define STRING_H

struct string {
	unsigned long length;
	char *buffer;
};

struct string *string_new(const char *buffer);
void string_free(struct string *str);

/*
 * Returns the C-style string.
 */
char *string_get_buffer(const struct string *str);
/*
 * Returns string's length.
 */
unsigned long string_length(const struct string *str);

#endif
