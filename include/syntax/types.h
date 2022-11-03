#pragma once

#include <set>
#include <lex/NextElement.h>

namespace syntax {
	enum class Types {
		boolean,
		natural_number,
		any,
		error
	};

	Types getType(const NextElement& el);

	bool operator < (Types l, Types r);
	bool operator <= (Types l, Types r);
}
