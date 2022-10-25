#pragma once
#include <identifiers.h>
#include <exception>

enum class ErrorType {
	lex,
	syntax
};

class Error {
public:
	Error() = delete;
	constexpr Error(ErrorType err);
	const ErrorType error;
};