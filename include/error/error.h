#pragma once
#include <identifiers.h>
#include <exception>

enum class ErrorType {
	lex,
	syntax
};

class Error {
public:

	template< typename From, typename To>
	static Error cannot_convert(ErrorType err);
	Error() = delete;
	constexpr Error(ErrorType err);
	constexpr Error(ErrorType err, const std::string& msg);
	const ErrorType error;
	const std::string message;
};