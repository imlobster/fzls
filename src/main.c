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

	// Width of the column (for table out)
	size_t colw = 0;

	Config cfg;

	// TODO: make arguments parser
	// TODO: support '-a'/'--all', '-w N','--width N', '-c'/'--colors', '--'
	cfg.path = ".";
	cfg.all = true;
	cfg.colors = true;
	cfg.termw = get_terminal_width();
	cfg.outt = OUT_TABLE;
	if(argc - 1 == 1) {
		cfg.path = argv[1];
	} else if(argc - 1 > 1) {
		fprintf(stderr, "fzls: arguments unvalued\n");
		return -1;
	}

	{
		Error err = fetch_for_units(cfg.all, cfg.path, &unitsc, &units, &colw);
		if(log_error(err) != 0) { exit(err); }
	}

	// Sort alphabetical
	qsort(units, unitsc, sizeof(FUnit), funit_name_compare);

	calculate_prefixes(unitsc, units);

	if(cfg.outt == OUT_ONECOL) { one_out(units, unitsc); }
	else if(cfg.outt == OUT_TABLE) { table_out(units, unitsc, cfg.termw, colw); }
	else { fprintf(stderr, "fzls: unknown output type\n"); }

	free_units(unitsc, units);
	return 0;
}
