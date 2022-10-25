#pragma once

#include <concepts.h>
#include <lex/lex_analise.h>
#include <vector>
#include <syntax/predicates.h>
#include <syntax/expression.h>
#include <syntax/structure.h>
#include <syntax/statement.h>
#include <assert.h>


namespace syntax {
	Statement parse(GetElement& gen);

	template<std::ranges::view View>
	std::pair<Expression, View> prase_bool_expression(View view)
	{
		auto current = view.begin();
		if (get_arity(*current) == 1) {
			auto parameter = current;
			++parameter;
			auto new_begin = parameter;
			++new_begin;
			return std::make_pair(
				Expression::create(*current, *parameter),
				std::ranges::subrange(new_begin, view.end())
			);
		}
		else if (is_value(*current) || current->lex == LexType::TokenVariable) {
			auto new_begin = current;
			++new_begin;
			return std::make_pair(
				Expression::create(*current),
				std::ranges::subrange(new_begin, view.end())
			);
		}
		else {
			auto op = current;
			++op;
			auto right = op;
			++right;
			auto new_begin = right;
			++new_begin;
			assert(get_arity(*op) == 2);
			return std::make_pair(
				Expression::create(*op, *current, *right),
				std::ranges::subrange(new_begin, view.end())
			);
		}
	}

	

	template<std::ranges::view View>
	std::pair< Statement, View> prase_statement(View view) {
		if (start_of_if(view)) {
			auto current = ++view.begin();
			auto exp_view_begin = prase_bool_expression(std::ranges::subrange(current, view.end()));
			current = exp_view_begin.second.begin();
			if (*current != Terminal::then_) {
				throw "error";
			}
			++current;
			auto state_true_view_begin = prase_statement(std::ranges::subrange(current, view.end()));
			current = state_true_view_begin.second.begin();
			if (*current != Terminal::else_) {
				throw "error";
			}
			++current;
			auto state_false_view_begin = prase_statement(std::ranges::subrange(current, view.end()));
			return std::make_pair(
				Statement::create(*view.begin(), exp_view_begin.first, state_true_view_begin.first, state_false_view_begin.first),
				state_false_view_begin.second
			);
		}
		else if (start_of_while(view)) {
			auto current = ++view.begin();
			auto exp_view_begin = prase_bool_expression(std::ranges::subrange(current, view.end()));
			current = exp_view_begin.second.begin();
			if (*current != Terminal::do_) {
				throw "error";
			}
			++current;
			auto state_true_view_begin = prase_statement(std::ranges::subrange(current, view.end()));
			return std::make_pair(
				Statement::create(*view.begin(), exp_view_begin.first, state_true_view_begin.first),
				state_true_view_begin.second
			);
		}
		else if (start_of_var_decl(view)) {
			auto var_name_itr = ++view.begin();
			auto new_begin = var_name_itr;
			++new_begin;
			if (*new_begin != Terminal::equal_assign_) {
				throw "error";
			}
			++new_begin;
			auto exp_view_begin = prase_bool_expression(std::ranges::subrange(new_begin, view.end()));
			return std::make_pair(
				Statement::create(*view.begin(), *var_name_itr, exp_view_begin.first),
				exp_view_begin.second
			);
		}
		else if (start_of_assigment(view)) {
			auto var_name_itr = view.begin();
			auto eql = var_name_itr;
			++eql;
			if (*eql != Terminal::equal_assign_) {
				throw "error";
			}
			auto new_begin = eql;
			++new_begin;
			auto exp_view_begin = prase_bool_expression(std::ranges::subrange(new_begin, view.end()));
			return std::make_pair(
				Statement::create(*eql, *var_name_itr, exp_view_begin.first),
				exp_view_begin.second
			);
		}
		else if(start_of_block(view) || start_of_protect(view)){
			auto state_true_view_begin = prase_statement(std::ranges::subrange(++view.begin(), view.end()));
			auto current = *state_true_view_begin.second.begin();
			if (current != Terminal::end_) {
				throw "error";
			}
			return std::make_pair(
				Statement::create(*view.begin(), state_true_view_begin.first),
				state_true_view_begin.second
			);

		}
		throw "error";
	}

	template<Terminal op, std::ranges::view View>
	std::pair<Statement, View> prase_statement_seq(View view) {
		std::vector<Statement> out_list;
		while (start_of_statement(view)) {
			auto statment_view = prase_statement(view);
			auto current = statment_view.second.begin();
			out_list.push_back(statment_view.first);
			view = statment_view.second;
			if (view.begin() != view.end()) {
				if (*view.begin() != op) {
					break;
				}
			}
		}
		return std::make_pair(Statement::create(op, out_list), view);
	}

	template<std::ranges::view View>
	auto parse(View view){
		for (const auto& el : view) {
			std::cout << el << " ";
		}
		if (start_of_exp_or_bool(view)) {
			throw "auto exp_view = prase_bool_expression(view)";
		}
		return prase_statement_seq<Terminal::seq_, View>(view);
	}
}

#include <syntax/format.h>