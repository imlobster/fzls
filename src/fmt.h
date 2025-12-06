#pragma once
#include <stddef.h>
#include <stdint.h>

#include "funit.h"

int count_chars_encodeagnostic(
	const char* is // 0 terminated string
);

uint8_t get_color_from_filetype(
	FType itype, // type of a file
	bool  iexe   // is file executable
);

void calculate_table(
	size_t  ic,     // count of the already inserted units
	int     itermw, // width of the terminal
	size_t* icolw,  // column width
	int*    ocols,  // calculated columns
	int*    orows   // calculated rows
);

void calculate_prefixes(
	size_t ic,    // count of the already inserted units
	FUnit* iunits // units array
);
