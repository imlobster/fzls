#include "fmt.h"

#include <stddef.h>
#include <string.h>

int count_chars_encodeagnostic(const char* is) {
	size_t w = 0; size_t slen = strlen(is);
	for (size_t i = 0; i < slen;) {
		unsigned char c = is[i];
		if       (c < 0x80)          { i += 1; }
		else if ((c & 0xE0) == 0xC0) { i += 2; }
		else if ((c & 0xF0) == 0xE0) { i += 3; }
		else if ((c & 0xF8) == 0xF0) { i += 4; }
		else                         { i++; continue; }
		++w;
	} return w;
}
