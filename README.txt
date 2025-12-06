	[ ! PROTOTYPE STAGE ! ]

fzls ('fuzzy list') is the successor to Unix ls, which
explicitly highlights the distinct prefixes of file names.

usage:
	-a/--all         show dotted files
	-c/--color       enable colors
	-w N/--width N   specify terminal width
	-1/--one-column  display in one column

	--               stop arguments parsing, promising the next argument will be path

	-?/--help        this text

compile it yourself:
	you must have CMake installed.

	linux:
		run ./build.sh

		if you are using mingw, uncomment the corresponding line
		in ./build.sh it will use default linux -> windows
		x86-64 configuration (./w64-mingw32.cmake). if this is
		not what you want, proceed to configure it manually.

	windows:
		mkdir build
		cd build
		cmake ..
		cmake --build . --config Release

config:
	fzls does not include dynamic configuration.
	it can be found at ./config.std.h
	to apply changes, recompile fzls.

how this can be helpful:

	imagine you have a folder:

# ls
important

	and you make a backup of it:

# cp -r important important-old
# ls
important      important-backup

	you did something with the first one and now you want to get
	rid of the backup.

	you would type this:

# ls
important      important-backup
# rm -rf i

	then, most likely, you will press the TAB. and after that,
	there are only two possible scenarios.

	first: you will find that you are very careful

# rm -rf i^I
important      important-backup
# rm-rf important-^I
# rm-rf important-backup

	second: you will get in trouble

# rm -rf
important      important-backup
# rm-rf important

	so how does fzls help in this situation? you will ALWAYS see
	what you need to type.

# fzls
|I|mportant      |IMPORTANT-|backup

	you will see that if you enter ONLY 'i', incorrect
	autocomplete may appear.

	and, of course, it does not actually look like that. The
	real fzls uses ansi escape codes instead of capital letters
	or additional characters.

so... yes. I would not say that it is impossible to live without
fzls, but if you encounter the same problems I did, feel free to
use it.

other flags, such as -l or --tree, are not planned, so use fzls
together with the standard ls or another program you prefer.
