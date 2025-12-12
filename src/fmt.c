#include "../config.h"
#include "stdconfig.h"

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

uint8_t get_color_from_filetype(FType itype, bool iexe) {
	switch(itype) {
		case FREGULAR: return iexe ? FILECOLOR_EXECUTABLE : FILECOLOR_REGULAR; break;
		case FDIRECTORY: return FILECOLOR_DIRECTORY; break;
		case FSYMLINK: return FILECOLOR_SYMLINK; break;
		default: return FILECOLOR_BROKEN; break;
	} return 39;
}

void calculate_table(size_t ic, int itermw, size_t* icolw, int* ocols, int* orows) {
	*icolw += FILENAME_PADDING;
	int cols = itermw / *icolw;
	if(cols <= 0) { cols = 1; }
	int rows = (ic + cols - 1) / cols;
	*ocols = cols; *orows = rows;
	return;
}

size_t common_diffw_(const char* ilhs, const char* irhs) {
	size_t w = 0;
	while(
		ilhs[w] && irhs[w]
		&& ilhs[w] == irhs[w]
	) { ++w; }
	return w;
}

// SOMEDAY: i will move it to prefix tree
void calculate_prefixes(size_t ic, FUnit* iunits) {
	// Iterate through every file unit
	for(size_t i = 0; i < ic; ++i) {
		size_t namew = strlen(iunits[i].name);
		size_t diffw = 0;

		#ifdef RAISE_PREFIX_MINIMUM_TO_2
			size_t min_diffw = (iunits[i].dot && namew >= 2) ? 2 : 1;
		#else
			size_t min_diffw = 1;
		#endif

		// Iterate through the name string
		for(size_t w = min_diffw; w <= namew; ++w) {
			size_t max_commonw = namew;

			// Iterate through every file unit
			for(size_t j = 0; j < ic; ++j) {
				if(i == j) { continue; }

				// If the other file is started with this->prefix
				if(strncmp(iunits[i].name, iunits[j].name, w) == 0) {
					size_t commonw = common_diffw_(iunits[i].name, iunits[j].name);
					if(commonw < max_commonw) { max_commonw = commonw; }
				}
			}

			// If the common diff is equal to this->name
			if(max_commonw == namew) { diffw = w; break; }
		}

		if(diffw == 0) { diffw = namew; }

		// Eat UTF-8
		while(
			diffw < namew &&
			(iunits[i].name[diffw] & 0xC0) == 0x80
		) { ++diffw; }

		iunits[i].diffw = diffw;
	}
	return;
}
