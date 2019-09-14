#ifndef HASH_H
#define HASH_H

/*
 * Useful link: http://www.cse.yorku.ca/~oz/hash.html
 */

unsigned long sdbm(const char *str);
unsigned long djb2(const char *str);

#endif
