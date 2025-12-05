#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "errors.h"
#include "funit.h"
#include "out.h"
#include "fmt.h"

#define FILENAME_PADDING 2

int main(int argc, char** argv) {
	FUnit* units = NULL; size_t unitsc = 0;

	const char* im_here = ".";

	// TODO: this also going somwhere to fmt/out
	int term_width = get_terminal_width();
	size_t col_width = 0;

	// TODO: make arguments parser
	// TODO: support '-a'/'--all', '-w N','--width N', '-c'/'--colors'
	if(argc - 1 == 1) {
		im_here = argv[1];
	} else if(argc - 1 > 1) {
		fprintf(stderr, "fzls: arguments unvalued\n");
		return -1;
	}

	{
		Error err = fetch_for_units(im_here, &unitsc, &units, &col_width);
		if(log_error(err) != 0) { exit(err); }
	}

	// Sort alphabetical
	qsort(units, unitsc, sizeof(FUnit), funit_name_compare);

	// TODO: move it somewhere
	{
		size_t displayed = 0;
		col_width += FILENAME_PADDING;

		int cols = term_width / col_width;
		if (cols == 0) cols = 1;
		size_t rows = (unitsc + cols - 1) / cols;

		fprintf(stdout, "\033[0m");

		for (size_t r = 0; r < rows; r++) {
		for (size_t c = 0; c < cols; c++) {
			size_t i = r + c * rows;
			if (i < unitsc) {
				switch(units[i].type) {
					case FREGULAR:
						if(!units[i].exe) { fprintf(stdout, "\033[0;0m%s\033[m", units[i].name); }
						else { fprintf(stdout, "\033[1;32m%s\033[m", units[i].name); }
					break;
					case FDIRECTORY: fprintf(stdout, "\033[1;34m%s\033[m", units[i].name); break;
					case FSYMLINK: fprintf(stdout, "\033[1;36m%s\033[m", units[i].name); break;
					default: fprintf(stdout, "\033[1;31m%s\033[m", units[i].name); break;
				}
				++displayed;

				// Offset
				for(size_t k = units[i].namedw; k < col_width; ++k) { fputc(' ', stdout); }
			}
		} fputc('\n', stdout); }
	}

	free_units(unitsc, units);
	return 0;
}
