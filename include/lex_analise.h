#pragma once

#include <iostream>
#include <string>
#include <identifiers.h>
#include <expected>
#include <error.h>

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

	LexType lex;
	union {
		Terminal terminal;
		Number number;
		std::string variable;
	};
	NextElement& operator = (const NextElement& other);
};
	
class GetChar {
public:
	typedef std::expected<NextElement, Error> Next;
	GetChar() = delete;
	GetChar(std::istream& in);
	Next operator()();

	bool eof();
protected:

	NextElement next();
	Number read_number(char current);
	std::string next_keyword();
	std::istream& input;
	size_t current_index;
};


std::ostream& operator << (std::ostream& out, const NextElement& next);