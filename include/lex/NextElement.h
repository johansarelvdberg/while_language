#pragma once

#include <string>
#include <identifiers.h>
#include <format>
#include <iosfwd>      // for ptrdiff_t, size_t
#include <iterator>    // for size
#include <stdexcept>   // for invalid_argument
#include <string_view> // for string_view


constexpr std::int32_t mystoi(std::string_view str, std::size_t* pos = nullptr) {
	//from https://stackoverflow.com/questions/25195176/how-do-i-convert-a-c-string-to-a-int-at-compile-time
	using namespace std::literals;
	const auto numbers = "0123456789"sv;

	const auto begin = str.find_first_of(numbers);
	if (begin == std::string_view::npos)
		throw std::invalid_argument{ "stoi" };

	const auto sign = begin != 0U && str[begin - 1U] == '-' ? -1 : 1;
	str.remove_prefix(begin);

	const auto end = str.find_first_not_of(numbers);
	if (end != std::string_view::npos)
		str.remove_suffix(std::size(str) - end);

	auto result = 0;
	auto multiplier = 1U;
	for (std::ptrdiff_t i = std::size(str) - 1U; i >= 0; --i) {
		auto number = str[i] - '0';
		result += number * multiplier * sign;
		multiplier *= 10U;
	}

	if (pos != nullptr) *pos = begin + std::size(str);
	return result;
}

class Number {
public:
	Number(const std::string& str) : num(mystoi(str)) {};
	size_t num;
};

class NextElement {
public:
	NextElement() = delete;
	NextElement(const NextElement& other);
	~NextElement();
	NextElement(LexType l, Terminal t);
	NextElement(LexType l, std::string t);
	NextElement(LexType l, Number n);

	friend bool operator == (const NextElement& left, Terminal right);
	friend bool operator != (const NextElement& left, Terminal right);
	LexType lex;
	union {
		Terminal terminal;
		Number number;
		std::string variable;
	};
	NextElement& operator = (const NextElement& other);
};


template <>
struct std::formatter<Number> : std::formatter<std::string> {
	auto format(Number p, format_context& ctx) {
		return formatter<string>::format(std::format("{}", p.num), ctx);
	}
};


template <>
struct std::formatter<NextElement> : std::formatter<std::string> {
	auto format(const NextElement& p, format_context& ctx) {
		switch (p.lex) {
		case LexType::Terminal:
			return formatter<string>::format(std::format("{{ \"type\": {}, \"value\": {} }}", p.lex, p.terminal), ctx);
			break;
		case LexType::TokenNumber:
			return formatter<string>::format(std::format("{{ \"type\": {}, \"value\": {} }}", p.lex, p.number), ctx);
			break;
		case LexType::TokenVariable:
			return formatter<string>::format(std::format("{{ \"type\": {}, \"value\": {} }}", p.lex, p.variable), ctx);
			break;
		}
	}
};
