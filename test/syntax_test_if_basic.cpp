#include <syntax/syntax.h>
#include <vector>
#include <string>
#include <array>
#include <iostream>
#include <sstream>



std::vector<std::pair<std::string, std::string>> test_data = {
	{"if true do var x = 0", ""}
};

int main() {
	bool pass = true;
	for (const auto& el : test_data) {
		std::vector<NextElement> lex_list;
		std::string mystr("if false then var x := false else var x := false");
		std::stringstream tmp(mystr);
		GetElement next(tmp);
		auto out = syntax::parse(next);
		auto out_str = std::format("{}", out);
		if (out_str != el.second) {
			std::cerr << out_str;
			return 1;
		}
	}
	return 0;
}