#include <syntax/types.h>

using namespace syntax;



Types syntax::getType(const NextElement& el)
{
	switch (el.lex) {
	default:
		return Types::error;
	case LexType::TokenNumber:
		return Types::natural_number;
	case LexType::TokenVariable:
		return Types::any;
	case LexType::Terminal:
		switch (el.terminal) {
		case Terminal::true_:
		case Terminal::false_:
			return Types::boolean;
		default:
			return Types::any;
		}
	}
}

bool syntax::operator<(Types l, Types r)
{
	return (int)l < (int)r;
}


bool syntax::operator<=(Types l, Types r)
{
	return (l == r) || (l < r);
}
