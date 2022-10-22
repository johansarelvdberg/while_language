#pragma once
#include <identifiers.h>
#include <exception>

class Error {
public:
	//Error() = delete;
	constexpr Error(size_t c_index);
	const size_t character_index;
};