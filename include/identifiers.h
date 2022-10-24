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
	plus_,
	seq_,
	minus_,
	times_,
	equal_,
	equal_assign_,
	less_equal_,
	not_,
	and_,
	true_,
	false_,
	void_,
	if_,
	then_,
	else_,
	do_,
	var_,
	while_,
	white_space_,
	begin_,
	end_,
	call_,
	par_,
	protect_,
	proc_,
	is_

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
		default:
			str = "lex type format not defined";
		}

		return formatter<string>::format(str, ctx);
	}
};
