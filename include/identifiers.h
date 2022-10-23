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
	plus_,
	seq_,
	minus_,
	times_,
	equal_,
	equal_assign_,
	less_equal_,
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
	while_,
	white_space_,
	begin_,
	end_,
	call_,
	par_,
	protect_,
	proc_,
	is_

};