#!/bin/sh

printf "analyzing...\n\n"

match_npragmaonce=$(find . -type f -name '*.h' -exec awk 'FNR==1{sub(/\r$/,""); if($0!="#pragma once") printf "\t%s\n", FILENAME}' {} +)

if [ -n "$match_npragmaonce" ]; then
	printf "\n\e[1;31mfounded header without '#pragma once'!\e[0m\n"
	printf "%s\n\n" "$match_npragmaonce"
fi

printf "\nbuilding...\n\n"

mkdir -p build
cd build || exit 1

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
#cmake .. -DCMAKE_TOOLCHAIN_FILE=../w64-mingw32.cmake
cmake --build .

cd ..
