
#include <syntax/expression.h>
#include <vector>

using namespace syntax;

struct BinaryTypeConvert{
	const ExpOp op;
	const Types left;
	const Types right;
	const Types result;
	const bool comm;
};

std::vector<BinaryTypeConvert> binaryTypeConvertList({
	{ExpOp::and_, Types::boolean, Types::boolean, Types::boolean, true},
	{ExpOp::equal_, Types::natural_number, Types::natural_number, Types::boolean, true},
	{ExpOp::less_equal_, Types::natural_number, Types::natural_number, Types::boolean, true},
	{ExpOp::plus_, Types::natural_number, Types::natural_number, Types::natural_number, true},
	{ExpOp::minus_, Types::natural_number, Types::natural_number, Types::natural_number, true},
	{ExpOp::times_, Types::natural_number, Types::natural_number, Types::natural_number, true},
});

Types getBinaryTypes(ExpOp op, Types tl, Types tr) {
	for (const auto& el : binaryTypeConvertList) {
		if (el.op == op) {
			if (el.left == tl && el.right == tr) {
				return el.result;
			}
			else if (el.comm && el.left == tr && el.right == tl) {
				return el.result;
			}
		}
	}
	return Types::any;
}


Types getBinaryTypes(ExpOp op, const NextElement& l, const NextElement& r) {
	auto tl = getType(l);
	auto tr = getType(r);
	return getBinaryTypes(op, tl, tr);
}


Types getTypes(const Expression& exp) {
	switch (exp.type) {
	case ExpType::terminal:
		return exp.uninary.possible_types();
	case ExpType::binary:
		return exp.binary.possible_types();
	default:
		return Types::error;
	}
}

std::expected<ExpOp, Error> to_exp_type(const NextElement& el) {
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
			return std::unexpected(Error::cannot_convert<NextElement, ExpOp>(ErrorType::lex));
		}
		break;
	default:
		return ExpOp::identity_;
	}
}






Types syntax::ExpressionTerminal::possible_types() const
{
	return  getType (this->current);
}



Types syntax::ExpressionUnirary::possible_types() const
{
	if (this->has_value()) {
		switch (this->op.value()) {
		case ExpOp::identity_:
			return getType(this->current);
		case ExpOp::not_: {
			auto t = getType(this->current);
			if (t == Types::boolean) {
				return Types::boolean;
			}
			else {
				return Types::error;
			}
		}
		}
	}
	return Types::error;
}

bool syntax::ExpressionUnirary::has_value() const{
	return this->op.has_value();
}

syntax::ExpressionBinary::ExpressionBinary(const NextElement& op_name, const NextElement& left_, const NextElement& right_)
	

Types syntax::ExpressionBinary::possible_types() const
{
	return getBinaryTypes(this->op, getType(this->left), getTypes(this->right));
}

bool syntax::ExpressionBinary::has_value() const
{
	return this->op.has_value();
}


