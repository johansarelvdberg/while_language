#pragma once
#include <lex/lex_analise.h>

namespace syntax {
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
	enum class ExpType {
		terminal,
		uninary,
		binary
	};

	class ExpressionTerminal {
	public:
		ExpressionTerminal(const NextElement& current);
		const NextElement current;
	};

	class ExpressionUnirary {
	public:	
		ExpressionUnirary(const NextElement& op_name, const NextElement& current);
		const NextElement current;
		const ExpOp op;
	};

	class ExpressionBinary {
	public:
		ExpressionBinary(const NextElement& op_name, const NextElement& left_, const NextElement& right_);
		const NextElement left;
		const NextElement right;
		const ExpOp op;
	};

	class Expression {
	public:
		Expression() = delete;		
		Expression(const Expression& data);

		static Expression create(const NextElement& el);
		static Expression create(const NextElement& op, const NextElement& par);
		static Expression create(const NextElement& op, const NextElement& left, const NextElement& right);
		~Expression();

		const ExpType type;
		union{
			size_t empty;
			ExpressionTerminal terminal;
			ExpressionBinary binary;
			ExpressionUnirary uninary;
		};

		bool is_terminal()const;
		bool is_uninrary()const;
		bool is_binary()const;
	protected:
		Expression(const ExpressionTerminal& data);
		Expression(const ExpressionUnirary& data);
		Expression(const ExpressionBinary& data);
	};
	
}
