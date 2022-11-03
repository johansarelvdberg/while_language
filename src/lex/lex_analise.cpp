#include <lex/lex_analise.h>
#include <string>
#include <algorithm>
#include <vector>
#include <error/error.h>
#include <cctype>

static const std::vector<std::pair<std::string, Terminal>> terminals_table = {
	{"/\\", Terminal::and_},
	{"true", Terminal::true_},
	{"false", Terminal::false_},
	{"<=", Terminal::less_equal_},
	{"not", Terminal::not_},
	{"var", Terminal::var_},
	{"void", Terminal::void_},
	{"if", Terminal::if_},
	{"then", Terminal::then_},
	{"else", Terminal::else_},
	{"while", Terminal::while_},
	{"do", Terminal::do_},
	{":=", Terminal::equal_assign_},
	{"begin", Terminal::begin_},
	{"end", Terminal::end_},
	{"par", Terminal::par_},
	{"call", Terminal::call_},
	{"protect", Terminal::protect_},
	{"proc", Terminal::proc_},
	{"is", Terminal::is_},
	{"[", Terminal::left_annotate_},
	{"]", Terminal::right_annotate_},
	{"fnc", Terminal::fence}
};



GetElement::GetElement(std::istream& in) : reader(in) {}

size_t sym_len(char c) {
	switch (c) {
	default:
		throw std::logic_error("Not defined");
		break;
	case 'i':	
	case 'd':
	case '<':
	case '/':
		return 2;
		break;
	case 'v': return 3;
		break;
	case 't':	
	case 'e':
		return 4;
		break;
	case 'f':
	case 'w':
		return 5;
		break;
	}
}


constexpr bool is_digit(char current) {
	switch (current) {
	default:
		return false;
		break;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return true;
		break;
	}
}

GetElement::Next GetElement::operator()()
{
	try {
		return GetElement::Next(next());
	}
	catch (const Error& exp) {
		return std::unexpected(exp);
	}
}

NextElement GetElement::next() {
	if (reader.eof()) {
		return NextElement(LexType::Terminal, Terminal::eof);
	}
	char current = *reader;
	++reader;	
	switch (current) {
	case ' ':
		return NextElement(LexType::Terminal, Terminal::white_space_);
	case '+':
		return NextElement(LexType::Terminal, Terminal::plus_);
	case '-':
		return NextElement(LexType::Terminal, Terminal::minus_);
	case '*':
		return NextElement(LexType::Terminal, Terminal::times_);
	case '=':
		return NextElement(LexType::Terminal, Terminal::equal_);
	case ';':
		return NextElement(LexType::Terminal, Terminal::seq_);
	default: {
		if (is_digit(current)) {
			return NextElement(LexType::TokenNumber, read_number(current));
		}
		else {
			std::string symbols = this->next_keyword(current);
			for (const auto& i : terminals_table) {
				if (symbols == i.first) {
					return NextElement(LexType::Terminal, i.second);
				}
			}
			return NextElement(LexType::TokenVariable, symbols);
		}
	}
	}
}

bool GetElement::eof() {
	return reader.eof();
}

Number GetElement::read_number(char current)
{
	std::string ret;
	//ret += current;
	char c = current;
	while (is_digit(c)) {
		ret += c;
		++reader;
		if (reader.eof()) {
			break;
		}
		c = *reader;
	}
	return Number(ret);
}

std::string GetElement::next_keyword(char prefix)
{
	std::string ret;
	ret += prefix;
	char c = *reader;
	for (c = *reader; !reader.eof(); ++reader) {
		c = *reader;
		if (std::isprint(c) && c != ' ') {
			ret += c;
		}
		else {
			break;
		}
	}

	return ret;
}

std::string string(LexType l) {
	switch (l) {
	case LexType::Terminal:
		return "terminal";
		break;
	case LexType::TokenNumber:
		return "Number";
		break;
	case LexType::TokenVariable:
		return "variable";
		break;
	default:
		throw std::logic_error("Not defined");
		break;
	}
}

std::string string(Number n) {
	return std::to_string(n.num);
}

std::string string(Terminal n) {
	return std::to_string((int)n);
}

std::ostream& operator<<(std::ostream& out, const NextElement& next)
{
	std::string out_str = std::format("<type: {}, ", next.lex);
	out << out_str;
	switch (next.lex)
	{
	default:
		break;
	case LexType::Terminal:
		out << std::format("value: {}>",next.terminal);
		break;
	case LexType::TokenNumber:
		out << std::format("value: {}>", next.number);
		break;
	case LexType::TokenVariable:
		out << std::format("value: {}>", next.variable);
		break;
	}
	return out;
}