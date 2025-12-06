#pragma once

typedef enum Error {
	ERR_NO,
	ERR_ALLOC_FAILED,
	ERR_PATH_TOO_LONG,
	ERR_FETCH_ERROR,
} Error;

int log_error(Error ie);
