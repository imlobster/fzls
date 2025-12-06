#include "config.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "args.h"
#include "errors.h"
#include "funit.h"
#include "out.h"
#include "fmt.h"

int main(int argc, char** argv) {
	// File units array
	FUnit* units = NULL; size_t unitsc = 0;

	// Config
	Config cfg;
	size_t colw = 0; // Width of the column (for table out)

	{ // Get config
		Error err = get_config_from_args(argc, argv, &cfg);
		if(log_error(err) != 0) { exit(err); }
	}

	{ // Get files
		Error err = fetch_for_units(cfg.all, cfg.path, &unitsc, &units, &colw);
		if(log_error(err) != 0) { exit(err); }
	}

	// Sort alphabetical
	qsort(units, unitsc, sizeof(FUnit), funit_name_compare);

	// fzls main function
	calculate_prefixes(unitsc, units);

	// Output files list on the screen
	if(cfg.outt == OUT_ONECOL) { one_out(units, unitsc, cfg.colors); }
	else if(cfg.outt == OUT_TABLE) { table_out(units, unitsc, cfg.termw, colw, cfg.colors); }
	else { fprintf(stderr, "fzls: unknown output type\n"); }

	free_units(unitsc, units);
	return 0;
}
