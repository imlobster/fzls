#include "out.h"

#ifdef _WIN32
	#include <windows.h>
#else
	#include <sys/ioctl.h>
	#include <unistd.h>
#endif

#ifndef TERMWIDTH_FALLBACK
	#define TERMWIDTH_FALLBACK 80
#endif

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
