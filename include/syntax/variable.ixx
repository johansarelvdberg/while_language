export module Syntax;

import <string>;
namespace syntax {
	export class Variable {
	public:
		Variable() = delete;
		Variable(std::string v) : name(std::move(v)) {}
		const std::string name;
	};
}
