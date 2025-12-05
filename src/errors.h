#pragma once

typedef enum Errors {
	ERR_NO,
	ERR_ALLOC_FAILED,
	ERR_PATH_TOO_LONG,
	ERR_FETCH_ERROR,
} Error;

int log_error(Error ie);
