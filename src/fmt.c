#include "fmt.h"

#include <stddef.h>
#include <string.h>

#include "funit.h"

int count_chars_encodeagnostic(const char* is) {
	size_t w = 0; size_t slen = strlen(is);
	for (size_t i = 0; i < slen;) {
		unsigned char c = is[i];
		if       (c < 0x80)          { i += 1; }
		else if ((c & 0xE0) == 0xC0) { i += 2; }
		else if ((c & 0xF0) == 0xE0) { i += 3; }
		else if ((c & 0xF8) == 0xF0) { i += 4; }
		else                         { i += 1; continue; }
		++w;
	} return w;
}

void calculate_prefixes(size_t ic, FUnit* iunits) {
	// Iterate through every unit
	for(size_t i = 0; i < ic; ++i) {
		size_t namew = strlen(iunits[i].name);

		// Iterate through every byte in the current unit filename
		for(size_t diffw = 1; diffw <= namew; ++diffw) {
			size_t matches = 0;

			// Compare current byte to others
			for(size_t j = 0; j < ic; ++j) {
				if(i == j) { continue; }
				if(strncmp(iunits[i].name, iunits[j].name, diffw) == 0) { ++matches; }
			}

			// If found unique prefix
			if(matches == 0) {
				while(
					diffw < namew &&
					(iunits[i].name[diffw] & 0xC0) == 0x80 // check for the continuation byte
				) { ++diffw; }
				// Found prefix
				iunits[i].diffw = diffw;
				break;
			}
		}

		if(iunits[i].diffw == 0) { iunits[i].diffw = namew; }
	}

	return;
}
