cmake_minimum_required(VERSION 3.1)
project(psychic-waffle
	LANGUAGES C
	VERSION 0.1
)

add_executable(psychic-waffle
	main.c
)
set_target_properties(psychic-waffle PROPERTIES
	C_STANDARD	99
)
target_compile_definitions(psychic-waffle
	PRIVATE
		_POSIX_C_SOURCE=199309L
)
