#include <lex/NextElement.h>
#include <stdexcept>
	

NextElement::NextElement(LexType l, Terminal t) : lex(l), terminal(t) {
	if (l != LexType::Terminal) {
		throw std::logic_error("LexType must be Terminal");
	}
}

NextElement::NextElement(LexType l, std::string t) : lex(l), variable(t) {}

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

bool operator == (const NextElement& left, Terminal right) {
	if (left.lex == LexType::Terminal) {
		return left.terminal == right;
	}
	return false;
}

bool operator != (const NextElement& left, Terminal right) {
	return !(left == right);
}