#include <lex_analise.h>
#include <string>
#include <algorithm>
#include <vector>
#include <error.h>

const std::vector<std::pair<std::string, Terminal>> terminals_table = {
	{"/\\", Terminal::and_},
	{"true", Terminal::true_},
	{"false", Terminal::false_},
	{"<=", Terminal::less_equal},
	{"not", Terminal::not_},
	{"void", Terminal::void_},
	{"if", Terminal::if_},
	{"then", Terminal::then_},
	{"else", Terminal::else_},
	{"while", Terminal::while_},
	{"do", Terminal::do_},
};


NextElement::NextElement(LexType l, Terminal t) : lex(l), terminal(t) {
	if (l != LexType::Terminal) {
		throw std::logic_error("LexType must be Terminal");
	}
}

NextElement::NextElement(LexType l, std::string t) : lex(l), variable(t){}

NextElement::NextElement(LexType l, Number n) : lex(l), number(n) {
	if (l != LexType::TokenNumber) {
		throw std::logic_error("LexType must be Token");
	}
}

NextElement::~NextElement() {
	switch (this->lex) {
	case LexType::TokenVariable:
		this->variable.~basic_string();
	}
}

NextElement::NextElement(const NextElement& other) : lex(LexType::undefined) {
	if (this->lex == LexType::TokenVariable) {
		this->variable.~basic_string();
	}
	switch (other.lex) {
	case LexType::Terminal:
		this->terminal = other.terminal;
		break;
	case LexType::TokenNumber:
		this->number = other.number;
		break;
	case LexType::TokenVariable:
		::new(&this->variable) std::string;
		this->variable = other.variable;
		break;
	default:
		throw std::logic_error("Not defined");
	}
	this->lex = other.lex;
}

NextElement& NextElement::operator=(const NextElement& other)
{
	if (this->lex == other.lex && this->lex == LexType::TokenVariable) {
		this->variable = other.variable;
	}
	else {
		if (this->lex == LexType::TokenVariable) {
			this->variable.~basic_string();
		}
		switch (other.lex) {
		case LexType::Terminal:
			this->terminal = other.terminal;
			break;
		case LexType::TokenNumber:
			this->number = other.number;
			break;
		case LexType::TokenVariable:
			::new(&this->variable) std::string;
			this->variable = other.variable;
			break;
		default:
			throw std::logic_error("Not defined");
		}
		this->lex = other.lex;
	}
	return *this;
}

GetChar::GetChar(std::istream& in) : input(in){
	current_index = 0;
}

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
	case 't':
	case 'v':
	case 'e':
		return 4;
		break;
	case 'f':
	case 'w':
		return 5;
		break;
	}
}

constexpr bool is_alpha(char c) {
	return ('a' <=  c) && (c <= 'z');
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

GetChar::Next GetChar::operator()()
{
	try {
		return GetChar::Next(next());
	}
	catch (const Error& exp) {
		return std::unexpected(exp);
	}
}

NextElement GetChar::next(){
		char current = input.get();
		++current_index;
		if (input.eof()) {
			return NextElement(LexType::Terminal, Terminal::eof);
		}
		switch (current) {
		case ' ':
			return this->next();
		case '+':
			return NextElement(LexType::Terminal, Terminal::plus);
		case '-':
			return NextElement(LexType::Terminal, Terminal::minus);
		case '*':
			return NextElement(LexType::Terminal, Terminal::times);
		case '=':
			return NextElement(LexType::Terminal, Terminal::equal);
		case ';':
			return NextElement(LexType::Terminal, Terminal::eo_statment);
		default: {
			if (is_digit(current)) {
				return NextElement(LexType::TokenNumber, read_number(current));
			}
			else {
				std::string symbols = current + this->next_keyword();
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

bool GetChar::eof(){
	return input.eof();
}

Number GetChar::read_number(char current)
{
	std::string ret;
	ret += current;
	char c;
	for (c = input.get(); is_digit(c); c = input.get()) {
		ret += c;
	}
	if (input.eof()) {
		throw std::logic_error("eof");
	}
	input.putback(c);
	return Number(ret);
}

std::string GetChar::next_keyword()
{
	std::string ret;
	++this->current_index;
	char c;
	for (c = input.get(); is_alpha(c) && !input.eof(); ++this->current_index, c = input.get()) {
		ret += c;
		
	}
	if (input.eof()) {
		throw std::logic_error("Not defined");
	}	
	return ret;
}

std::string string(LexType l) {
	switch (l) {
	case LexType::Terminal:
		return "terminal";
		break;
	case LexType::TokenNumber:
		return "token";
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
	out << "<" << string(next.lex) << ", ";
	switch (next.lex)
	{
	default:
		break;
	case LexType::Terminal:
		out << string(next.terminal);
		break;
	case LexType::TokenNumber:
		out << string(next.number);
		break;
	}
	return out << ">";
}