#include "formatter.h"
#include <stdio.h>

void formatter_indent(int level)
{
	for (int i = 0; i < level; ++i)
		putchar('\t');
}
