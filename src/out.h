#pragma once
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "funit.h"

typedef enum OutType {
	OUT_ONECOL,
	OUT_TABLE,
} OutType;

void print_funit(
	uint8_t icolor, // color code of this file unit
	size_t  idiffw, // diff slice of this file unit
	char*   iname,  // filename of this file unit
	bool    icolors // will colors be printed
);

void one_out(
	FUnit* iunits,  // units array
	size_t iunitsc, // count of the already inserted units
	bool   icolors  // will colors be printed
);

void table_out(
	FUnit* iunits,  // units array
	size_t iunitsc, // count of the already inserted units
	int    itermw,  // terminal width
	size_t icolw,   // column width
	bool   icolors  // will colors be printed
);

int get_terminal_width(void);
