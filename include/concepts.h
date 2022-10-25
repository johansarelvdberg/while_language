#pragma once

#include <lex/lex_analise.h>


template<typename T>
concept LexGen = requires(T a)
{
    { a() } -> std::same_as<std::expected<NextElement, Error>>;
};
