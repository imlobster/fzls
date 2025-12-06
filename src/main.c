#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "config.h"
#include "errors.h"
#include "funit.h"
#include "out.h"
#include "fmt.h"


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

	calculate_prefixes(unitsc, units);

	// TODO: move it somewhere
	{
		col_width += FILENAME_PADDING;

		int cols = term_width / col_width;
		if (cols == 0) cols = 1;
		int rows = (unitsc + cols - 1) / cols;

		for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			size_t i = r + c * rows;
			if (i < unitsc) {
				uint8_t color = 0;

				switch(units[i].type) {
					case FREGULAR:
						if(!units[i].exe) { color = FILECOLOR_REGULAR; }
						else { color = FILECOLOR_EXECUTABLE; }
					break;
					case FDIRECTORY: color = FILECOLOR_DIRECTORY; break;
					case FSYMLINK: color = FILECOLOR_SYMLINK; break;
					default: color = FILECOLOR_BROKEN; break;
				}

				fprintf(stdout,
					"\033[0;"
						FILENAME_DIFF_ATTR
					";%hhum%.*s\033[0;"
						FILENAME_DEFAULT_ATTR
					";%hhum%s\033[0m",

					color,

					(int)units[i].diffw,
					units[i].name,

					color,

					units[i].name + units[i].diffw
				);

				// Offset
				for(size_t k = units[i].namedw; k < col_width; ++k) { fputc(' ', stdout); }
			}
		} fputc('\n', stdout); }
	}

	free_units(unitsc, units);
	return 0;
}
