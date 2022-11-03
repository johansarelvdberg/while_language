#pragma once

#include <memory>
#include <vector>

import Syntax;

namespace syntax {
	class Statement;
	class StatementIf;
	class StatementWhile;
	class StatementAssign;
	class StatementDecl;
	class StatementPar;
	class StatementSeq;
	class StatementProtect;
	class StatementBlock;

	enum class StatementOp {
		undefined,
		begin_,
		protected_,
		seq_,
		if_,
		while_,
		var_,
		assigment_,
		par_
	};

	class Statement : public SyntaxBase {
	public:
		Statement() = delete;

		static Statement create(const NextElement& syntax_id, const Expression& expression, const Statement& true_statement, const Statement& false_statement);
		static Statement create(const NextElement& syntax_id, const Expression& expression, const Statement& true_statement);
		static Statement create(const NextElement& syntax_id, const NextElement& var_name, const Expression& expression);
		static Statement create(const NextElement& syntax_id, const Statement& true_statement);
		static Statement create(Terminal syntax_id, const std::vector<Statement> & statemets);

		Statement(const Statement& other);
		~Statement();

		StatementOp op;
		union {
			std::shared_ptr<StatementIf> if_statement;
			std::shared_ptr<StatementWhile> while_statement;
			std::shared_ptr<StatementAssign> assign_statement;
			std::shared_ptr<StatementDecl> decl_statement;
			std::shared_ptr<StatementPar> par_statements;
			std::shared_ptr<StatementSeq> seq_statements;
			std::shared_ptr<StatementBlock> block_statement;
			std::shared_ptr<StatementProtect> protect_statement;
		};
	protected:
		Statement(const NextElement& syntax_id, const Expression& expression, const Statement& true_statement, const Statement& false_statement);
		Statement(const NextElement& syntax_id, const Expression& expression, const Statement& true_statement);
		Statement(const NextElement& syntax_id, const NextElement& var_name, const Expression& expression);
		Statement(const NextElement& syntax_id, const Statement& true_statement);
		Statement(Terminal syntax_id, const std::vector<Statement>& statemets);
	private:
		Statement(const NextElement& op);
		Statement(Terminal op);

		void init(StatementOp op);
	};

	class StatementIf {
	public:
		StatementIf() = delete;
		StatementIf(const Expression& cond, const Statement& left, const Statement& right);		

		Expression condition;
		Statement true_branch;
		Statement false_branch;
	};

	class StatementWhile {
	public:
		StatementWhile() = delete;
		StatementWhile(const Expression& cond, const Statement& body);

		const Expression condition;
		const Statement body;
	};

	class StatementAssign {
	public:
		StatementAssign() = delete;
		StatementAssign(const NextElement& cond, const Expression& body);

		const ExpressionTerminal var_name;
		const Expression expression;
	};

	class StatementDecl {
	public:
		StatementDecl() = delete;
		StatementDecl(const NextElement& var, const Expression& body);

		const ExpressionTerminal var_name;
		const Expression expression;
	};

	template<bool is_block>
	class Statement_Block_Protect {
	public:
		Statement_Block_Protect() = delete;
		Statement_Block_Protect(const Statement& statements_) : statements(statements_) {};

		const Statement statements;		
	};

	class StatementBlock : public Statement_Block_Protect<true> {};
	class StatementProtect : public Statement_Block_Protect<false> {};

	template<bool paralell>
	class Statement_Seq_Par {
	public:
		Statement_Seq_Par() = delete;
		Statement_Seq_Par(const std::vector<Statement>& statements_) : statements(statements_) {};
		const std::vector<Statement> statements;
	};

	class StatementPar : public Statement_Seq_Par<true> {};
	class StatementSeq : public Statement_Seq_Par<false> {};
};

