#include <syntax/expression.h>

using namespace syntax;


ExpOp to_exp_type(const NextElement& el) {
	switch (el.lex)
	{
	case LexType::Terminal:
		switch (el.terminal) {
		case Terminal::plus_:
			return ExpOp::minus_;
		case Terminal::minus_:
			return ExpOp::minus_;
		case Terminal::times_:
			return ExpOp::times_;
		case Terminal::equal_:
			return ExpOp::equal_;
		case Terminal::not_:
			return ExpOp::not_;
		case Terminal::less_equal_:
			return ExpOp::less_equal_;
		default:
			throw "error";
		}
		break;
	default:
		return ExpOp::identity_;
	}
}

Expression::Expression(const Expression& data) : SyntaxBase(false), empty(0), type(data.type)
{
	if (data.is_binary()) {
		new (&binary) ExpressionBinary(data.binary);
	}
	else if (data.is_terminal()) {
		new (&binary) ExpressionTerminal(data.terminal);
	}
	else if (data.is_uninrary()) {
		new (&binary) ExpressionUnirary(data.uninary);
	}
}

Expression syntax::Expression::create(const NextElement& el){
	return Expression(ExpressionTerminal(el));
}

Expression syntax::Expression::create(const NextElement& op, const NextElement& par)
{
	return Expression(ExpressionUnirary(op, par));
}

Expression syntax::Expression::create(const NextElement& op, const NextElement& left, const NextElement& right)
{
	return Expression(ExpressionBinary(op, left, right));
}

syntax::Expression::~Expression()
{
	if (this->is_binary()) {
		this->binary.~ExpressionBinary();
	}
	else if (this->is_terminal()) {
		this->terminal.~ExpressionTerminal();
	}
	else {
		this->uninary.~ExpressionUnirary();
	}
}

bool syntax::Expression::is_terminal() const
{
	return type == ExpType::terminal;
}

bool syntax::Expression::is_uninrary() const
{
	return type == ExpType::uninary;
}

bool syntax::Expression::is_binary() const
{
	return type == ExpType::binary;
}

syntax::Expression::Expression(const ExpressionTerminal& data) : SyntaxBase(false), type(ExpType::terminal), terminal(data){}

syntax::Expression::Expression(const ExpressionUnirary& data) : SyntaxBase(false), type(ExpType::uninary), uninary(data){}

syntax::Expression::Expression(const ExpressionBinary& data) : SyntaxBase(false), type(ExpType::binary), binary(data){}

syntax::ExpressionTerminal::ExpressionTerminal(const NextElement& current_) : current(current_){}

syntax::ExpressionUnirary::ExpressionUnirary(const NextElement& op_name, const NextElement& current_) : 
	op(to_exp_type(op_name)), current(current_){}

syntax::ExpressionBinary::ExpressionBinary(const NextElement& op_name, const NextElement& left_, const NextElement& right_)
	: op(to_exp_type(op_name)), left(left_), right(right_){}

