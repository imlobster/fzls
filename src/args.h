#pragma once
#include <stdbool.h>

#include "out.h"

typedef struct Config {
	char*   path;   // path that will be fetched
	int     termw;  // terminal width
	OutType outt;
	bool    all;    // will dotted files be shown
	bool    colors; // will color config be applied (attrs only since there is no more suitable way to display difference but with colors)
} Config;
