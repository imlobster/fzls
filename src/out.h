#pragma once
#include <stddef.h>
#include <stdbool.h>

#include "funit.h"

typedef enum OutType {
	OUT_ONECOL,
	OUT_TABLE,
} OutType;

void one_out(
	FUnit* iunits, // units array
	size_t iunitsc // count of the already inserted units
);

void table_out(
	FUnit* iunits,  // units array
	size_t iunitsc, // count of the already inserted units
	int itermw,     // terminal width
	size_t icolw    // column width
);

int get_terminal_width(void);
