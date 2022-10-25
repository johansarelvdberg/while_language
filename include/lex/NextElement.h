#pragma once

#include <string>
#include <identifiers.h>
#include <format>

class Number {
public:
	Number(std::string& str) : num(std::stoi(str)) {};
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
