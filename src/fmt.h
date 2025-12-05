#pragma once
#include <stddef.h>

#include "funit.h"

int count_chars_encodeagnostic(
	const char* is // 0 terminated string
);

void calculate_prefixes(
	size_t ic,    // count of the already inserted units
	FUnit* iunits // units array
);
