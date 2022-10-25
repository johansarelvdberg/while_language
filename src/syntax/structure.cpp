#include <syntax/structure.h>

size_t get_arity(const NextElement& el)
{
	switch (el.lex) {
	case LexType::TokenNumber:
	case LexType::TokenVariable:
		return 0;
	case LexType::Terminal:
		switch (el.terminal) {
		case Terminal::if_:
			return 3;
		case Terminal::and_:
		case Terminal::equal_:
		case Terminal::equal_assign_:
		case Terminal::less_equal_:
		case Terminal::minus_:
			return 2;
		case Terminal::not_:
		case Terminal::var_:
			return 1;
		case Terminal::true_:
		case Terminal::false_:
		case Terminal::void_:
		case Terminal::while_:
			return 0;
		}

	}
	throw "error";
}
