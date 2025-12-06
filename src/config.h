#pragma once

	/* Fuzzy List Config */

// Raise minimal prefix for the dotted files
// to avoid collisions with '..' suggestion
#define RAISE_PREFIX_MINIMUM_TO_2

// What terminal width will fzls use as a fallback
#define TERMWIDTH_FALLBACK 80

// Padding between filenames in row
#define FILENAME_PADDING 2

// Colors for the file types
/* Color format:
        Black  Red  Green  Yellow  Blue  Magenta  Cyan  White  Default
Normal  30     31   32     33      34    35       36    37     39
Bright  90     91   92     93      94    95       96    96
*/
#define FILECOLOR_REGULAR    39
#define FILECOLOR_DIRECTORY  34
#define FILECOLOR_SYMLINK    36
#define FILECOLOR_EXECUTABLE 32		// for the files with +x permissions (Linux only)

#define FILECOLOR_BROKEN     31

// ANSI Escape attributes
/* Format:
	Bold              1
	Dim               2
	Italic            3
	Underscore        4
	Flicker (Slow)    5
	Flicker (Fast)    6
	Inverse           7
	Crossed           8
*/
#define FILENAME_DIFF_ATTR    "7"		// for the prefix: |I|
#define FILENAME_DEFAULT_ATTR "0"		// for the rest of a filename: mportant








// The code below is not a part of the config.

#ifndef TERMWIDTH_FALLBACK
	#define TERMWIDTH_FALLBACK 80
#endif
#ifndef FILENAME_PADDING
	#define FILENAME_PADDING 2
#endif
#ifndef FILECOLOR_REGULAR
	#define FILECOLOR_REGULAR 39
#endif
#ifndef FILECOLOR_DIRECTORY
	#define FILECOLOR_DIRECTORY 34
#endif
#ifndef FILECOLOR_SYMLINK
	#define FILECOLOR_SYMLINK 36
#endif
#ifndef FILECOLOR_EXECUTABLE
	#define FILECOLOR_EXECUTABLE 32
#endif
#ifndef FILECOLOR_BROKEN
	#define FILECOLOR_BROKEN 31
#endif
#ifndef FILENAME_DIFF_ATTR
	#define FILENAME_DIFF_ATTR "7"
#endif
#ifndef FILENAME_DEFAULT_ATTR
	#define FILENAME_DEFAULT_ATTR "0"
#endif
