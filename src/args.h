#pragma once
#include <stdbool.h>

#include "errors.h"
#include "out.h"

typedef struct Config {
	char*   path;   // path that will be fetched
	int     termw;  // terminal width
	OutType outt;   // out format
	bool    all;    // will dotted files be shown
	bool    colors; // will color config be applied (attrs only since there is no more suitable way to display difference but with colors)
} Config;

Error get_config_from_args(
	int     ic,  // arguments count
	char**  iv,  // array of arguments
	Config* ocfg // output
);
