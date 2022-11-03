#pragma once

export module Syntax;

import <lex/lex_analise.h>;
import <syntax/syntax_base.h>;
import <memory>;
import <vector>;


namespace syntax {

	class Expression;

	enum class ExpOp {
		identity_,
		true_,
		plus_,
		minus_,
		times_,
		false_,
		and_,
		less_equal_,
		equal_,
		var_,
		not_
	};

	

	constexpr size_t getArity(ExpOp op) {
		switch (op) {
		case ExpOp::and_:
		case ExpOp::equal_:
		case ExpOp::less_equal_:
		case ExpOp::minus_:
		case ExpOp::plus_:
		case ExpOp::times_:
		case ExpOp::var_:
			return 2;
			break;
		case ExpOp::false_:
		case ExpOp::true_:
			return 0;
			break;
		case ExpOp::identity_:
		case ExpOp::not_:
			return 1;
			break;
		}
	}

	

	export class Expression : public SyntaxBase {
	public:
		Expression() = delete;
		
	
		const size_t arity;
		std::vector<Expression> parameters;

	protected:
		

		
	};
}
