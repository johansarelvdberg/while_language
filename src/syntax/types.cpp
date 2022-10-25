
#include <syntax/types.h>

using namespace syntax;

TypeOptions::TypeOptions() : options({Types::any}) {}
TypeOptions::TypeOptions(std::initializer_list<Types> data) : options(data.begin(), data.end()) {};