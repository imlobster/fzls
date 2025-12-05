#pragma once
#include <stddef.h>
#include <stdbool.h>

#include "errors.h"

typedef enum FType {
	FBROKEN,
	FREGULAR,
	FDIRECTORY,
	FSYMLINK,
} FType;

typedef struct FUnit {
	char*  name;   // filename
	size_t namedw; // display width of the filename
	size_t diffw;  // real width of the filename unique prefix
	FType  type;   // file kind
	bool   dot;    // is the filename begins with '.'
	bool   exe;    // is the file is executable
} FUnit;

int funit_name_compare(
	const void* ilhs, // void == FUnit
	const void* irhs  // void == FUnit
);

Error fetch_for_units(
	const char* ipath,  // path to be fetched
	size_t*     oc,     // total of fetched units
	FUnit**     ounits, // units array
	size_t*     omaxdw  // longest display width
);

void free_units(
	size_t ic,    // count of the already inserted units
	FUnit* iunits // units array
);
