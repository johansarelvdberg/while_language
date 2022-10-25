#include <lex/lex_analise.h>
#include <vector>
#include <string>
#include <array>
#include <iostream>
#include <sstream>



std::vector<std::pair<std::string, std::vector<std::string>>> test_data = {
	{"while true do var x = 0", {
		"{ \"type\": terminal, \"value\": while }",
		"{ \"type\": terminal, \"value\": white_space }", 
		"{ \"type\": terminal, \"value\": true }",
		"{ \"type\": terminal, \"value\": white_space }",
		"{ \"type\": terminal, \"value\": do }",
		"{ \"type\": terminal, \"value\": white_space }",
		"{ \"type\": terminal, \"value\": var }",
		"{ \"type\": terminal, \"value\": white_space }",
		"{ \"type\": variable, \"value\": x }",
		"{ \"type\": terminal, \"value\": white_space }",
		"{ \"type\": terminal, \"value\": equal }",
		"{ \"type\": terminal, \"value\": white_space }",
		"{ \"type\": terminal, \"value\": eof }"}}
};

int main() {
	bool pass = true;
	for (const auto& el : test_data) {
		std::string mystr(el.first);
		std::stringstream tmp(mystr);
		auto parsed = GetElement(tmp);
		size_t i = 0;
		do {
			auto parsed_str = std::format("{}", parsed().value());
			if ( parsed_str != el.second[i]) {
				std::cerr << parsed_str << "\t" << el.second[i];
				return 1;
			}			
			++i;
		} while (!parsed.eof());
	}
	return 0;
}