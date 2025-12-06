#include "funit.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <dirent.h>
	#include <sys/stat.h>
	#include <unistd.h>
	#include <limits.h>
#endif

#include "errors.h"
#include "fmt.h"

int funit_name_compare(const void* ilhs, const void* irhs) {
	const FUnit* lhs = (const FUnit *)ilhs;
	const FUnit* rhs = (const FUnit *)irhs;
	return strcmp(lhs->name, rhs->name);
}

void free_units(size_t ic, FUnit* iunits) {
	if(ic <= 0) { free(iunits); return; }
	for(size_t i = 0; i < ic; ++i) { free(iunits[i].name); }
	free(iunits); return;
}

Error fetch_for_units(bool iidots, const char* ipath, size_t* oc, FUnit** ounits, size_t* omaxdw) {
	#define GROWTH_FACTOR 4
	size_t s_capacity = 16;
	size_t s_count = 0;
	FUnit* units = malloc(s_capacity * sizeof(FUnit));
	if(!units) { return ERR_ALLOC_FAILED; }

	size_t max_display_width = 0;

	#ifdef _WIN32
		wchar_t path[MAX_PATH];
		if(MultiByteToWideChar(CP_UTF8, 0, ipath, -1, path, MAX_PATH) == 0) { free(units); return ERR_PATH_TOO_LONG; }

		wcscat_s(path, MAX_PATH, L"\\*");

		WIN32_FIND_DATAW find_data;
		HANDLE find_handle = FindFirstFileW(path, &find_data);

		if(find_handle == INVALID_HANDLE_VALUE) { free(units); return ERR_FETCH_ERROR; }

		do {
			if(s_count >= s_capacity) {
				s_capacity *= GROWTH_FACTOR;
				FUnit* new_units = realloc(units, s_capacity * sizeof(FUnit));
				if(new_units == NULL) { free_units(s_count, units); return ERR_ALLOC_FAILED; }
				units = new_units;
			}

			// Skip dotted files if allowed
			if(find_data.cFileName[0] == L'.' && !iidots) { continue; }

			// Skip '.' and '..' as they are useless for 'fzls' purposes
			if(wcscmp(find_data.cFileName, L".") == 0 || wcscmp(find_data.cFileName, L"..") == 0) { continue; }

			{ // Take name
				int utf8w = WideCharToMultiByte(CP_UTF8, 0, find_data.cFileName, -1, NULL, 0, NULL, NULL);
				if(utf8w == 0) { free_units(s_count, units); return ERR_ALLOC_FAILED; }
				units[s_count].name = malloc(utf8w);
				if(units[s_count].name == NULL) { free_units(s_count, units); return ERR_ALLOC_FAILED; }
				if(WideCharToMultiByte(CP_UTF8, 0, find_data.cFileName, -1, units[s_count].name, utf8w, NULL, NULL) == 0) {
					free(units[s_count].name);
					free_units(s_count, units);
					return ERR_ALLOC_FAILED;
				}
			}

			// Take name width and calculate longest
			{
				size_t namedw = count_chars_encodeagnostic(units[s_count].name);
				if (namedw > max_display_width) max_display_width = namedw;
				units[s_count].namedw = namedw;
			}

			// Deciding if the file is 'private'
			// Direct access because NULL was checked.
			units[s_count].dot = units[s_count].name[0] == '.';

			// Take file type
			if(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				units[s_count].type = FDIRECTORY;
			} else if(find_data.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) {
				units[s_count].type = FSYMLINK;
			} else {
				units[s_count].type = FREGULAR;
			}

			// On Windows executableness doesnt make sense
			units[s_count].exe = false;

			++s_count;
		} while(FindNextFileW(find_handle, &find_data));

		FindClose(find_handle);
	#else
		DIR* dir = opendir(ipath);

		if(!dir) { free(units); return ERR_FETCH_ERROR; }

		struct dirent* entry;
		struct stat fstatus;
		while((entry = readdir(dir)) != NULL) {
			if(s_count >= s_capacity) {
				s_capacity *= GROWTH_FACTOR;
				FUnit* new_units = realloc(units, s_capacity * sizeof(FUnit));
				if(new_units == NULL) { free_units(s_count, units); return ERR_ALLOC_FAILED; }
				units = new_units;
			}

			// Skip dotted files if allowed
			if(entry->d_name[0] == '.' && !iidots) { continue; }

			// Skip '.' and '..' as they are useless for 'fzls' purposes
			if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) { continue; }

			// Take name
			units[s_count].name = strdup(entry->d_name);
			if(units[s_count].name == NULL) { free_units(s_count, units); return ERR_ALLOC_FAILED; }

			// Take name width and calculate longest
			{
				size_t namedw = count_chars_encodeagnostic(units[s_count].name);
				if (namedw > max_display_width) max_display_width = namedw;
				units[s_count].namedw = namedw;
			}

			// Deciding if the file is 'private'
			// Direct access because NULL was checked.
			units[s_count].dot = units[s_count].name[0] == '.';

			// Take this entry path
			char path[PATH_MAX]; {
				int written = snprintf(path, PATH_MAX, "%s/%s", ipath, entry->d_name);
				if(written > PATH_MAX) { free_units(s_count, units); return ERR_PATH_TOO_LONG; }
			}

			// Take file type
			if(lstat(path, &fstatus) == 0) {
				if(S_ISDIR(fstatus.st_mode)) {
					units[s_count].type = FDIRECTORY;
				} else if(S_ISLNK(fstatus.st_mode)) {
					units[s_count].type = FSYMLINK;
				} else {
					units[s_count].type = FREGULAR;
				}

				// Check is the file is executable
				if(S_ISREG(fstatus.st_mode) &&
					(fstatus.st_mode) & (
						S_IXUSR |
						S_IXGRP |
						S_IXOTH
					)
				) {
					units[s_count].exe = true;
				} else { units[s_count].exe = false; }
			} else { units[s_count].type = FBROKEN; }

			++s_count;
		}

		closedir(dir);
	#endif

	*ounits = units;
	*oc = s_count;
	*omaxdw = max_display_width;
	#undef GROWTH_FACTOR
	return ERR_NO;
}
