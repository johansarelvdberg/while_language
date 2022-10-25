#pragma once
#include <syntax/types.h>
 namespace syntax {
	class SyntaxBase {
	public:
		SyntaxBase() = delete;
		SyntaxBase(bool err) : error(err) {};
		inline bool operator()()const { return !error; }
		const bool error;
	};
}
