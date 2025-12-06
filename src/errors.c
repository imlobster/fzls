#include "errors.h"

#include <stdio.h>

int log_error(Error ie) {
	if(ie != ERR_NO) {
		switch(ie) {
			case ERR_ALLOC_FAILED:    fprintf(stderr, "fzls: bad allocation\n"); break;
			case ERR_PATH_TOO_LONG:   fprintf(stderr, "fzls: invalid path\n"); break;
			case ERR_FETCH_ERROR:     fprintf(stderr, "fzls: unable to open directory\n"); break;
			case ERR_ARGS_LENGTH_ERR: fprintf(stderr, "fzls: not enough arguments\n"); break;
			case ERR_ARGS_TOO_MANY:    fprintf(stderr, "fzls: too many arguments\n"); break;
			default:                  fprintf(stderr, "fzls: unknown error\n"); break;
		} return 1;
	} return 0;
}
