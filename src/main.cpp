
#include "lex/lex_analise.h"
#include <string>
#include <iostream>
#include <sstream> 
#include <vector>
#include <algorithm>


import Syntax;

bool is_eof(std::expected<NextElement, Error> c) {
	if (c) {
		if (c.value().lex == LexType::Terminal) {
			if (c.value().terminal == Terminal::eof) {
				return true;
			}
		}
	}
	return false;
}

int main() {

	std::vector<NextElement> lex_list;
	std::string mystr("if false then var x := false else var x := false");
	std::stringstream tmp(mystr);
	GetElement next(tmp);
	auto out = syntax::parse(next);
	return 0;
}
