#pragma once

typedef enum Error {
	ERR_NO,
	ERR_ALLOC_FAILED,
	ERR_PATH_TOO_LONG,
	ERR_FETCH_ERROR,
	ERR_ARGS_LENGTH_ERR,
	ERR_ARGS_TOO_MANY,
} Error;

int log_error(Error ie);
