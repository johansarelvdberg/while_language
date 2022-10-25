#pragma once
#include <format>

enum class LexType {
	undefined,
	Terminal,
	TokenNumber,
	TokenVariable
};


enum class Terminal {
	undefined = 0,
	eof = 1,
	plus_ = 2,
	seq_ = 3,
	minus_ = 4,
	times_ = 5,
	equal_ = 6,
	equal_assign_ = 7,
	less_equal_ = 8,
	not_ = 9,
	true_ = 10,
	false_ = 11,
	void_ = 12,
	if_ = 13,
	then_ = 14,
	else_ = 15,
	do_ = 16,
	var_ = 17,
	while_ = 18,
	white_space_ = 19,
	begin_ = 20,
	end_ = 21,
	call_ = 22,
	par_ = 23,
	protect_ = 24,
	proc_ = 25,
	is_ = 26,
	and_ = 27,
};

template <>
struct std::formatter<LexType> : std::formatter<std::string> {
	auto format(LexType p, format_context& ctx) {
		std::string str;
		switch (p) {
		case LexType::Terminal:
			str = "terminal";
			break;
		case LexType::TokenNumber:
			str = "number";
			break;
		case LexType::TokenVariable:
			str = "variable";
			break;
		case LexType::undefined:
			str = "undefined";
			break;
		default:
			str = "lex type format not defined";
		}

		return formatter<string>::format(str, ctx);
	}
};

template <>
struct std::formatter<Terminal> : std::formatter<std::string> {
	auto format(Terminal p, format_context& ctx) {
		std::string str;
		switch (p) {
		case Terminal::proc_:
			str = "process";
			break;
		case Terminal::eof:
			str = "eof";
			break;
		case Terminal::plus_:
			str = "plus";
			break;
		case Terminal::begin_:
			str = "begin";
			break;
		case Terminal::call_:
			str = "call";
			break;
		case Terminal::do_:
			str = "do";
			break;
		case Terminal::else_:
			str = "else";
			break;
		case Terminal::end_:
			str = "end";
			break;
		case Terminal::equal_:
			str = "equal";
			break;
		case Terminal::equal_assign_:
			str = "equal_assign";
			break;
		case Terminal::false_:
			str = "false";
			break;
		case Terminal::if_:
			str = "if";
			break;
		case Terminal::is_:
			str = "is";
			break;
		case Terminal::less_equal_:
			str = "less_equal";
			break;
		case Terminal::minus_:
			str = "minus";
			break;
		case Terminal::not_:
			str = "not";
			break;
		case Terminal::par_:
			str = "paralell";
			break;
		case Terminal::protect_:
			str = "protected";
			break;
		case Terminal::seq_:
			str = "sequential";
			break;
		case Terminal::then_:
			str = "then";
			break;
		case Terminal::times_:
			str = "times";
			break;
		case Terminal::true_:
			str = "true";
			break;
		case Terminal::var_:
			str = "var";
			break;
		case Terminal::void_:
			str = "void";
			break;
		case Terminal::while_:
			str = "while";
			break;
		case Terminal::undefined:
			str = "undefined";
			break;
		case Terminal::white_space_:
			str = "white_space";
			break;
		default:
			str = "lex type format not defined: " + std::to_string((int)p);
		}

		return formatter<string>::format(str, ctx);
	}
};
