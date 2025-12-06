cmake_minimum_required(VERSION 3.14...3.31)
project(fzls LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SOURCES
	src/main.c
	src/funit.c
	src/out.c
	src/errors.c
	src/fmt.c
)

add_executable(fzls ${SOURCES})

if (CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID MATCHES "Clang")
	target_compile_options(fzls PRIVATE
		-flto -ffast-math -ffast-math

		-Ofast

		-Wall -Wextra -Werror=return-type
	)
elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(fzls PRIVATE
        /O2
        /W4
        /permissive-
    )
endif()
