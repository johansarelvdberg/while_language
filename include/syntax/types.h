#pragma once

#include <set>

namespace syntax {
	enum class Types {
		boolean,
		natural_number,
		undefined,
		any
	};

	class TypeOptions {
	public:
		TypeOptions();
		TypeOptions(std::initializer_list<Types> data);

		const std::set<Types> options;
	};
}
