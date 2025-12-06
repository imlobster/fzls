#include "../config.h"
#include "out.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "fmt.h"

#ifdef _WIN32
	#include <windows.h>
#else
	#include <sys/ioctl.h>
	#include <unistd.h>
#endif

void print_funit(uint8_t icolor, size_t idiffw, char* iname, bool icolors) {
	if(!icolors) {
		fprintf(stdout,
			"\033["
				FILENAME_DIFF_ATTR
			"m%.*s\033[0;"
				FILENAME_DEFAULT_ATTR
			"m%s\033[m",

			(int)idiffw, // Diff size
			iname,       // Diff slice

			iname + idiffw // Rest slice
		);
	} else {
		fprintf(stdout,
			"\033[0;"
				FILENAME_DIFF_ATTR
			";%hhum%.*s\033[0;"
				FILENAME_DEFAULT_ATTR
			";%hhum%s\033[m",

			icolor, // Diff color

			(int)idiffw, // Diff size
			iname,       // Diff slice

			icolor, // Rest color

			iname + idiffw // Rest slice
		);
	}
}

void table_out(FUnit* iunits, size_t iunitsc, int itermw, size_t icolw, bool icolors) {
	if(iunitsc <= 0) { return; }
	int cols, rows; calculate_table(iunitsc, itermw, &icolw, &cols, &rows);
	char* spacesbuf = malloc(icolw); memset(spacesbuf, ' ', icolw);

	for(int r = 0; r < rows; r++) {
	for(int c = 0; c < cols; c++) {
		size_t i = r + c * rows; if(i >= iunitsc) { break; }

		uint8_t color = FILECOLOR_BROKEN; if(icolors) { color = get_color_from_filetype(iunits[i].type, iunits[i].exe); }

		print_funit(color, iunits[i].diffw, iunits[i].name, icolors);

		// Column offset
		size_t spacesn = icolw - iunits[i].namedw;
		if(spacesn > 0 && i != iunitsc - 1) { fwrite(spacesbuf, 1, spacesn, stdout); }
	} fputc('\n', stdout); }

	free(spacesbuf);
	return;
}

void one_out(FUnit* iunits, size_t iunitsc, bool icolors) {
	if(iunitsc <= 0) { return; }
	for(size_t i = 0; i < iunitsc; ++i) {
		uint8_t color = FILECOLOR_BROKEN; if(icolors) { color = get_color_from_filetype(iunits[i].type, iunits[i].exe); }
		print_funit(color, iunits[i].diffw, iunits[i].name, icolors);
		fputc('\n', stdout);
	} return;
}

int get_terminal_width(void) {
	#ifdef _WIN32
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		HANDLE stdout_handler = GetStdHandle(STD_OUTPUT_HANDLE);

		if(!GetConsoleScreenBufferInfo(stdout_handler, &csbi)) { return TERMWIDTH_FALLBACK; }
		return csbi.srWindow.Right - csbi.srWindow.Left + 1;
	#else
		struct winsize w;

		if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) { return TERMWIDTH_FALLBACK; }
		return w.ws_col;
	#endif
}
