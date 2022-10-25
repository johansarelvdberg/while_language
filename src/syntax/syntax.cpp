#include <syntax/syntax.h>
#include <syntax/statement.h>

using namespace syntax;

Statement syntax::parse(GetElement& next)
{
	std::vector< NextElement> data_list;
	while (!next.eof()) {
		auto c = next();
		if (c) {
			const auto& now = c.value();
			bool add = true;
			if (now.lex == LexType::Terminal) {
				if (now.terminal == Terminal::white_space_) {
					add = false;
				}
			}
			if (add) {
				data_list.push_back(now);
			}
			//std::cout << now << " ";
			if (now.lex == LexType::Terminal && now.terminal == Terminal::eof) {
				break;
			}
		}
		else {
			//error handeling XXX
			break;
		}
	}
	return syntax::parse(std::ranges::subrange(data_list.begin(), data_list.end())).first;	
}

