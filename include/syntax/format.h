
#pragma once

#include <syntax/syntax.h>


template <typename Value>
struct std::formatter<std::vector<Value>> : std::formatter<std::string> {
	auto format(const std::vector<Value>& v, format_context& ctx) {

		auto&& out = ctx.out();
		format_to(out, "[");
		if (v.size() > 0)
			format_to(out, "{}", v[0]);
		for (int i = 1; i < v.size(); ++i)
			format_to(out, ", {}", v[i]);
		return format_to(out, "]");
	}
	// ...
};


template <>
struct std::formatter<syntax::StatementOp> : std::formatter<std::string> {
	auto format(syntax::StatementOp p, format_context& ctx) {
		using namespace syntax;
		std::string str;
		switch (p) {
		case StatementOp::begin_:
			str = "begin";
			break;
		case StatementOp::assigment_:
			str = "assigment";
			break;
		case StatementOp::if_:
			str = "if";
			break;
		case StatementOp::par_:
			str = "paralell";
			break;
		case StatementOp::protected_:
			str = "protected";
			break;
		case StatementOp::seq_:
			str = "sequence";
			break;
		case StatementOp::var_:
			str = "var";
			break;
		case StatementOp::while_:
			str = "while";
			break;
		case StatementOp::undefined:
			str = "undefined";
			break;
		default:
			str = "lex type format not defined";
		}

		return formatter<string>::format(str, ctx);
	}
};

template <>
struct std::formatter<syntax::Statement> : std::formatter<std::string> {
	auto format(syntax::Statement p, format_context& ctx) {
		using namespace syntax;
		std::string str = std::format("{{\"type\": {}, ", p.op);
		switch (p.op) {
		case StatementOp::begin_:
			str += std::format("{} }}", *p.block_statement);
			break;
		case StatementOp::assigment_:
			str += std::format("{} }}", *p.assign_statement);
			break;
		case StatementOp::if_:
			str += std::format("{} }}", *p.if_statement);
			break;
		case StatementOp::par_:
			str += std::format("{} }}", *p.par_statements);
			break;
		case StatementOp::protected_:
			str += std::format("{} }}", *p.protect_statement);
			break;
		case StatementOp::seq_:
			str += std::format("{} }}", *p.seq_statements);
			break;
		case StatementOp::var_:
			str += std::format("{} }}", *p.decl_statement);
			break;
		case StatementOp::while_:
			str += std::format("{} }}", *p.while_statement);
			break;
		case StatementOp::undefined:
			str = "undefined";
			break;
		default:
			str = "lex type format not defined";
		}

		return formatter<string>::format(str, ctx);
	}
};

template <>
struct std::formatter<syntax::StatementIf> : std::formatter<std::string> {
	auto format(const syntax::StatementIf& p, format_context& ctx) {
		using namespace syntax;
		return 	std::formatter<std::string>::format(
			std::format("\"condition\": {}, \"true_branch\": {}, \"false_branch\": {} ",
				p.condition, p.true_branch, p.false_branch),
			ctx);
	}
};

template <>
struct std::formatter<syntax::StatementWhile> : std::formatter<std::string> {
	auto format(const syntax::StatementWhile& p, format_context& ctx) {
		using namespace syntax;
		return std::formatter<std::string>::format(
			std::format(
				"\"condition\": {}, \"body\": {}",
				StatementOp::while_, p.condition, p.body),
			ctx);
	}
};

template <>
struct std::formatter<syntax::StatementAssign> : std::formatter<std::string> {
	auto format(const syntax::StatementAssign& p, format_context& ctx) {
		using namespace syntax;
		return std::formatter<std::string>::format(
			std::format(
				"\"varialbe\": {}, \"expression\": {}",
				StatementOp::assigment_, p.var_name, p.expression),
			ctx);
	}
};

template <>
struct std::formatter<syntax::StatementDecl> : std::formatter<std::string> {
	auto format(const syntax::StatementDecl& p, format_context& ctx) {
		using namespace syntax;
		return std::formatter<std::string>::format(
			std::format(
				"\"varialbe\": {}, \"expression\": {}",
				p.var_name, p.expression), ctx);
	}
};


template <>
struct std::formatter<syntax::StatementBlock> : std::formatter<std::string> {
	auto format(const syntax::StatementBlock& p, format_context& ctx) {
		using namespace syntax;
		return std::formatter<std::string>::format(
			std::format(
				"\"body\": {}",
				p.statements), ctx);
	}
};


template <>
struct std::formatter<syntax::StatementProtect> : std::formatter<std::string> {
	auto format(const syntax::StatementProtect& p, format_context& ctx) {
		using namespace syntax;
		return std::formatter<std::string>::format(
			std::format(
				"\"body\": {}",
				StatementOp::protected_, p.statements), ctx);
	}
};

template <>
struct std::formatter<syntax::StatementPar> : std::formatter<std::string> {
	auto format(const syntax::StatementPar& p, format_context& ctx) {
		using namespace syntax;
		return std::formatter<std::string>::format(
			std::format(
				"\"body\": {}",
				p.statements), ctx);
	}
};

template <>
struct std::formatter<syntax::StatementSeq> : std::formatter<std::string> {
	auto format(const syntax::StatementSeq& p, format_context& ctx) {
		using namespace syntax;
		return std::formatter<std::string>::format(
			std::format(
				"\"body\": {}",
				p.statements), ctx);
	}
};





/// 
/// ////////expresion
/// 


#if 0
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
#endif


template <>
struct std::formatter<syntax::ExpOp> : std::formatter<std::string> {
	auto format(const syntax::ExpOp& p, format_context& ctx) {
		using namespace syntax;
		switch (p) {
		case ExpOp::identity_:
			return std::formatter<std::string>::format(std::string("identity"), ctx);
			break;
		case ExpOp::true_:
			return std::formatter<std::string>::format(std::string("true"), ctx);
			break;
		case ExpOp::plus_:
			return std::formatter<std::string>::format(std::string("plus"), ctx);
			break;
		case ExpOp::minus_:
			return std::formatter<std::string>::format(std::string("minus"), ctx);
			break;
		case ExpOp::times_:
			return std::formatter<std::string>::format(std::string("times"), ctx);
			break;
		case ExpOp::false_:
			return std::formatter<std::string>::format(std::string("false"), ctx);
			break;
		case ExpOp::and_:
			return std::formatter<std::string>::format(std::string("and"), ctx);
			break;
		case ExpOp::less_equal_:
			return std::formatter<std::string>::format(std::string("less_equal"), ctx);
			break;
		case ExpOp::equal_:
			return std::formatter<std::string>::format(std::string("equal"), ctx);
			break;
		case ExpOp::var_:
			return std::formatter<std::string>::format(std::string("var"), ctx);
			break;
		case ExpOp::not_:
			return std::formatter<std::string>::format(std::string("not"), ctx);
			break;
		}
	}
};

template <>
struct std::formatter<syntax::ExpType> : std::formatter<std::string> {
	auto format(const syntax::ExpType& p, format_context& ctx) {
		using namespace syntax;
		switch (p) {
		case ExpType::terminal:
			return std::formatter<std::string>::format(std::string("terminal"), ctx);
			break;
		case ExpType::uninary:
			return std::formatter<std::string>::format(std::string("uninary"), ctx);
			break;
		case ExpType::binary:
			return std::formatter<std::string>::format(std::string("binary"), ctx);
			break;
		}
	}
};






template <>
struct std::formatter<syntax::Expression> : std::formatter<std::string> {
	auto format(const syntax::Expression& p, format_context& ctx) {
		using namespace syntax;
		if (p.is_binary()) {
			return std::formatter<std::string>::format(std::format("{{\"type\": {}, \"value\": {} }}", p.type, p.binary), ctx);
		}
		else if (p.is_terminal()) {
			return std::formatter<std::string>::format(std::format("{{\"type\": {}, \"value\": {} }}", p.type, p.terminal), ctx);
		}
		else if (p.is_uninrary()) {
			return std::formatter<std::string>::format(std::format("{{\"type\": {}, \"value\": {} }}", p.type, p.uninary), ctx);
		}
	}
};

template <>
struct std::formatter<syntax::ExpressionTerminal> : std::formatter<std::string> {
	auto format(const syntax::ExpressionTerminal& p, format_context& ctx) {
		using namespace syntax;
		return std::formatter<std::string>::format(std::format("{{ {} }}", p.current), ctx);
	}
};


template <>
struct std::formatter<syntax::ExpressionUnirary> : std::formatter<std::string> {
	auto format(const syntax::ExpressionUnirary& p, format_context& ctx) {
		using namespace syntax;
		return std::formatter<std::string>::format(std::format("{{\"operation\": {}, \"data\": {} }}", p.op.value(), p.current), ctx);
	}
};

template <>
struct std::formatter<syntax::ExpressionBinary> : std::formatter<std::string> {
	auto format(const syntax::ExpressionBinary& p, format_context& ctx) {
		using namespace syntax;
		return std::formatter<std::string>::format(std::format("{{\"operation\": {}, \"left\": {}, \"right\": {} }}", p.op.value(), p.left, p.right), ctx);
	}
};