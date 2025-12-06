#include "args.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "errors.h"
#include "out.h"

Error get_config_from_args(int ic, char** iv, Config* ocfg) {
	ocfg->path = NULL;
	ocfg->termw = get_terminal_width();
	ocfg->outt = OUT_TABLE;
	ocfg->all = false;
	ocfg->colors = false;

	for(int i = 1; i < ic; ++i) {
		char* arg = iv[i];
#define CHECK_FLAG(ismall, ifull) (strcmp(arg, ismall) == 0 || strcmp(arg, ifull) == 0)

		if     (CHECK_FLAG("-a", "--all"))        { ocfg->all = true; }
		else if(CHECK_FLAG("-c", "--color"))      { ocfg->colors = true; }
		else if(CHECK_FLAG("-1", "--one-column")) { ocfg->outt = OUT_ONECOL; }

		else if(CHECK_FLAG("-w", "--width")) {
			if(i + 1 >= ic) { return ERR_ARGS_LENGTH_ERR; }
			ocfg->termw = atoi(iv[++i]);
			continue;
		}

		// Skipper
		else if(strcmp(arg, "--") == 0) {
			if(i + 1 >= ic) { return ERR_ARGS_LENGTH_ERR; }
			ocfg->path = iv[++i];
			break;
		}

		else {
			if(ocfg->path != NULL) { return ERR_ARGS_TOO_MANY; }
			ocfg->path = arg;
			continue;
		}
#undef CHECK_FLAG
	}

	if(ocfg->path == NULL) { ocfg->path = "."; }

	return ERR_NO;
}
