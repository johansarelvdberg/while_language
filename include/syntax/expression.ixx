
export module Syntax : Expression;


import <lex/lex_analise.h>;
import <syntax/syntax_base.h>;
import <memory>;
import <vector>;





namespace syntax {
	class Variable;
	export typedef std::expected<Variable, Error> VariableError;

	export class Variable {
	public:	
		static VariableError create(const NextElement& v) {
			switch (v.lex) {
			default:
				return std::unexpected(Error());
			case LexType::TokenVariable:
				return std::expected<Variable, Error>(Variable(v.variable));
			}
		};
		const std::string name;
	protected:
		Variable() =default;
		Variable(const std::string& v) : name(v) {}
		Variable(std::string&& v) : name(std::move(v)) {}
	};
}


namespace syntax {

	class Expression;

	export enum class ExpOp {
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
		return 0;
	}

	
	class ExpressionTerminal;

	export class Expression : public SyntaxBase {
	public:
		Expression() = delete;
		Expression(ExpOp op_) :op(op_) {}
		const ExpOp op;
		std::vector<Expression> parameters;

		static ExpressionTerminal create_ternimal(const NextElement& v);
	};

	class ExpressionTerminal : Expression {
	public:
		const NextElement value;
		friend Expression;
	protected:
		ExpressionTerminal(const NextElement& v) : Expression(ExpOp::identity_), value(v) {}
	};


	ExpressionTerminal Expression::create_ternimal(const NextElement& v)
	{
		return ExpressionTerminal(v);
	}
}
