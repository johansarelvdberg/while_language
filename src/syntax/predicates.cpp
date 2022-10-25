#include <syntax/predicates.h>


bool syntax::is_value(const NextElement& el)
{
	if (el.lex == LexType::Terminal) {
		switch (el.terminal) {
		case Terminal::false_:
		case Terminal::true_:
		case Terminal::void_:
			return true;
			break;

		}
	}
	else if (el.lex == LexType::TokenNumber) {
		return true;
	}
	return false;
}
