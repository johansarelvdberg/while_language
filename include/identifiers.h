#pragma once


enum class LexType {
	undefined,
	Terminal,
	TokenNumber,
	TokenVariable
};


enum class Terminal {
	undefined = 0,
	eof = 1,
	plus,
	eo_statment,
	minus,
	times,
	equal,
	equal_assign,
	less_equal,
	not_,
	and_,
	true_,
	false_,
	void_,
	if_,
	then_,
	else_,
	do_,
	var_,
	while_

};