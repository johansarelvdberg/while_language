#pragma once

#include <iostream>
#include <string>
#include <identifiers.h>
#include <expected>
#include <error.h>
#include <ranges>
#include <iterator>
#include <lex/NextElement.h>



class GetChar {
public:
	GetChar(std::istream& in) : begin(in) {
		char_count = 0;
	};
	bool eof() const { return begin == end; };
	char operator*() { 

		return *begin; 
	};
	GetChar& operator++() { 
		if (!eof()) { 
			++char_count; 
			++begin; 
		}
		return *this;
	}
protected:
	size_t char_count;
	std::istreambuf_iterator<char> begin;
	std::istreambuf_iterator<char> end;
};

class GetElement {
public:
	typedef std::expected<NextElement, Error> Next;
	GetElement() = delete;	
	GetElement(std::istream& in);
	Next operator()();
	bool eof();
protected:
	GetChar reader;	
	NextElement next();
	Number read_number(char current);
	std::string next_keyword(char prefix);	
};


std::ostream& operator << (std::ostream& out, const NextElement& next);