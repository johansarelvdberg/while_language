
#include "lex_analise.h"
#include <string>
#include <iostream>
#include <sstream> 
#include <vector>
#include <algorithm>

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
	std::string mystr("+-109; if ;qaswed;");
	
	std::stringstream tmp(mystr);

	GetChar next(tmp);


	while (!next.eof()) {
		auto c = next();
		if (c) {
			const auto& now = c.value();
			lex_list.push_back(now);
			//std::cout << now << " ";
			if (now.lex == LexType::Terminal && now.terminal == Terminal::eof) {
				break;
			}
		}
		else {
			//error handeling XXX
			break;
		}
	}

	for (const auto& i : lex_list) {
		std::cout << i << " ";
	}

	return 0;
}
