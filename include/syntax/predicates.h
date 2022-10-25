#pragma once
#include <lex/NextElement.h>
#include <ranges>
namespace syntax {

	template<std::ranges::range Range>
	inline bool not_empty(const Range& r) {
		return r.begin() != r.end();
	}

	template<std::ranges::range Range>
	inline bool empty(const Range& r) {
		return r.begin() == r.end();
	}

	bool is_value(const NextElement& el);

	template<std::ranges::view View>
	bool start_of_exp_or_bool(View view);

	template<std::ranges::view View>
	bool start_of_if(View view);

	template<std::ranges::view View>
	bool start_of_while(View view);

	template<std::ranges::view View>
	bool start_of_var_decl(View view);

	template<std::ranges::view View>
	bool start_of_assigment(View view);

	template<std::ranges::view View>
	bool start_of_exp_or_bool(View view)
	{
		auto current = view.begin();
		if (current->lex == LexType::Terminal) {
			switch (current->terminal)
			{
			case Terminal::not_:
			case Terminal::true_:
			case Terminal::false_:
				return true;
			default:
				break;
			}
		}
		else if (current->lex == LexType::TokenNumber) {
			return true;
		}
		else if (current->lex == LexType::TokenVariable) {
			++current;
			if (current == view.end()) {
				throw "error";
			}
			if (current->lex == LexType::Terminal) {
				switch (current->terminal)
				{
				case Terminal::equal_:
				case Terminal::plus_:
				case Terminal::minus_:
				case Terminal::times_:
				case Terminal::and_:
				case Terminal::less_equal_:
					return true;
				default:
					break;
				}
			}
		}
		return false;
	}

	template<std::ranges::view View>
	bool start_of_var_decl(View view)
	{
		auto current = view.begin();
		return not_empty(view) && (current->terminal == Terminal::var_);
	}

	template<std::ranges::view View>
	bool start_of_assigment(View view)
	{
		if (not_empty(view)) {
			auto current = view.begin();
			if (current->lex == LexType::TokenVariable) {
				++current;
				return not_empty(view) && (current->terminal == Terminal::equal_assign_);
			}
		}
		return false;
	}


	template<std::ranges::view View>
	bool start_of_while(View view)
	{
		return not_empty(view) && (*view.begin() == Terminal::while_);
	}

	template<std::ranges::view View>
	bool start_of_block(View view)
	{
		return not_empty(view) && (*view.begin() == Terminal::begin_);
	}

	template<std::ranges::view View>
	bool start_of_protect(View view)
	{
		return not_empty(view) && (* view.begin() == Terminal::protect_);
	}

	template<std::ranges::view View>
	bool start_of_if(View view) {
		return not_empty(view) && (*view.begin() == Terminal::if_);
	}

	template<std::ranges::view View>
	bool start_of_statement(View view) {
		return not_empty(view) && (start_of_assigment(view) || start_of_if(view) || start_of_var_decl(view) || start_of_while(view));
	}
}
