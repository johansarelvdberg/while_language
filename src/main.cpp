
#include "lex/lex_analise.h"
#include <string>
#include <iostream>
#include <sstream> 
#include <vector>
#include <algorithm>
#include<syntax/syntax.h>

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
	syntax::parse(next);
	return 0;
}
