#include <syntax/statement.h>
#include <vector>

using namespace syntax;

static const std::vector<std::pair<Terminal, StatementOp>> terminals_table = {
	{Terminal::equal_assign_, StatementOp::assigment_},
	{Terminal::if_, StatementOp::if_},
	{Terminal::while_, StatementOp::while_},
	{Terminal::var_, StatementOp::var_},
	{Terminal::seq_, StatementOp::seq_}
};

StatementOp to_statement_op(const NextElement& syntax_id) {
	for (const auto& el : terminals_table) {
		if (syntax_id == el.first) {
			return el.second;
		}
	}
	throw "error";
}

StatementOp to_statement_op(Terminal syntax_id) {
	for (const auto& el : terminals_table) {
		if (syntax_id == el.first) {
			return el.second;
		}
	}
	throw "error";
}

Statement Statement::create(const NextElement& syntax_id, const Expression& expression, const Statement& true_statement, const Statement& false_statement)
{
	return Statement(syntax_id, expression, true_statement, false_statement);
}

Statement Statement::create(const NextElement& syntax_id, const Expression& expression, const Statement& true_statement)
{
	return Statement(syntax_id, expression, true_statement);
}

Statement Statement::create(const NextElement& syntax_id, const NextElement& var_name, const Expression& expression)
{
	return Statement(syntax_id, var_name, expression);
}

Statement Statement::create(const NextElement& syntax_id, const Statement& true_statement) {
	return Statement(syntax_id, true_statement);
}

Statement Statement::create(Terminal syntax_id, const std::vector<Statement>& statemets) {
	if (statemets.size() == 1) {
		return statemets[0];
	}
	else {
		return Statement(syntax_id, statemets);
	}
}

Statement::Statement(const NextElement& op_)  {
	this->op = to_statement_op(op_);
	init(this->op);
}

Statement::Statement(Terminal op_)  {
	this->op = to_statement_op(op_);
	init(this->op);
}

syntax::Statement::Statement(const Statement& other) {
	this->~Statement();
	this->init(other.op);
	switch (this->op) {
	case StatementOp::if_:
		this->if_statement = other.if_statement;
		break;
	case StatementOp::while_:
		this->while_statement = other.while_statement;
		break;
	case StatementOp::assigment_:
		this->assign_statement = other.assign_statement;
		break;
	case StatementOp::var_:
		this->decl_statement = other.decl_statement;
		break;
	case StatementOp::seq_:
		this->seq_statements = other.seq_statements;
		break;
	case StatementOp::par_:
		this->par_statements = other.par_statements;
		break;
	default:
		throw "error"; 
		break;
	}
	
}

syntax::Statement::~Statement()
{
	switch (this->op) {
	case StatementOp::if_:
		this->if_statement.~shared_ptr();
		break;
	case StatementOp::while_:
		this->while_statement.~shared_ptr();
		break;
	case StatementOp::assigment_:
		this->assign_statement.~shared_ptr();
		break;
	case StatementOp::var_:
		this->decl_statement.~shared_ptr();
		break;
	case StatementOp::seq_:
		this->seq_statements.~shared_ptr();
		break;
	case StatementOp::par_:
		this->par_statements.~shared_ptr();
		break;
	case StatementOp::begin_:
		this->block_statement.~shared_ptr();
		break;
	case StatementOp::protected_:
		this->protect_statement.~shared_ptr();
		break;
	}
}

Statement::Statement(const NextElement& syntax_id, const Expression& expression, const Statement& true_statement, const Statement& false_statement) : Statement(syntax_id)
{
	switch (op) {
	case StatementOp::if_:
		if_statement = std::shared_ptr<StatementIf>(new StatementIf(expression, true_statement, false_statement));
		break;
	default:
		throw "error";
		break;
	}
}

Statement::Statement(const NextElement& syntax_id, const Expression& expression, const Statement& true_statement) : Statement(syntax_id)
{
	switch (op) {
	case StatementOp::while_:
		while_statement = std::shared_ptr<StatementWhile>(new StatementWhile(expression, true_statement));
		break;
	default:
		throw "error";
		break;
	}
}

Statement::Statement(const NextElement& syntax_id, const NextElement& var_name, const Expression& expression) : Statement(syntax_id)
{
	switch (op) {
	case StatementOp::assigment_:
		assign_statement = std::shared_ptr<StatementAssign>(new StatementAssign(var_name, expression));
		break;
	case StatementOp::var_:
		decl_statement = std::shared_ptr< StatementDecl>(new StatementDecl(var_name, expression));
		break;
	default:
		throw "error";
		break;
	}
}

Statement::Statement(const NextElement& syntax_id, const Statement& statement) : Statement(syntax_id) {
	switch (op) {
	case StatementOp::begin_:
		block_statement = std::shared_ptr< StatementBlock>(new StatementBlock(statement));
		break;
	case StatementOp::protected_:
		protect_statement = std::shared_ptr< StatementProtect>(new StatementProtect(statement));
		break;
	}
}

Statement::Statement(Terminal syntax_id, const std::vector<Statement>& statemets) : Statement(syntax_id) {
	switch (op) {
	case StatementOp::seq_:
		seq_statements = std::shared_ptr<StatementSeq>(new StatementSeq(statemets));
		break;
	case StatementOp::par_:
		par_statements = std::shared_ptr<StatementPar>(new StatementPar(statemets));
		break;
	default:
		throw "error";
		break;
	}
}

void syntax::Statement::init(StatementOp op)
{
	this->op = op;
	switch (this->op) {
	case StatementOp::assigment_:
		new(&assign_statement) std::shared_ptr<StatementAssign>;
		break;
	case StatementOp::while_:
		new(&while_statement) std::shared_ptr<StatementWhile>;
		break;
	case StatementOp::if_:
		new(&if_statement) std::shared_ptr<StatementIf>;
		break;
	case StatementOp::var_:
		new(&decl_statement) std::shared_ptr< StatementDecl>;
		break;
	case StatementOp::seq_:
		new(&seq_statements) std::shared_ptr< StatementSeq>;
		break;
	case StatementOp::par_:
		new(&par_statements) std::shared_ptr< StatementPar>;
		break;
	case StatementOp::begin_:
		new(&block_statement) std::shared_ptr< StatementBlock>;
		break;
	case StatementOp::protected_:
		new(&protect_statement) std::shared_ptr< StatementProtect>;
		break;
	}
}

StatementIf::StatementIf(const Expression& cond, const Statement& left, const Statement& right): condition(cond), true_branch(left), false_branch(right){}

StatementWhile::StatementWhile(const Expression& cond, const Statement& body_) : condition(cond), body(body_){}

StatementAssign::StatementAssign(const NextElement& var, const Expression& body) : var_name(var), expression(body){}

syntax::StatementDecl::StatementDecl(const NextElement& var, const Expression& body) : var_name(var), expression(body) {}
