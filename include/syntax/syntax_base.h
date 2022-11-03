#pragma once
#include <syntax/types.h>
 namespace syntax {
	class SyntaxBase {
	public:
		SyntaxBase() { error = false; }		
		inline bool operator()()const { return !contain_error(); }
		bool contain_error()const {return error; }
	protected:
		bool error;
	};
}
