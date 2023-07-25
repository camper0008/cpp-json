#pragma once

#include <cstddef>
#include <string>

enum class TokenType {
    RBrace,
    LBrace,
    RBracket,
    LBracket,
    Int,
    Decimal,
    String,
    Colon,
    Comma,
    True,
    False,
    Null,
    Eof,
};

struct Token {
    TokenType type;
    size_t position;
    size_t length;
    size_t line;
    size_t column;
};

class Lexer {
private:
    std::string text;
    size_t position = 0;
    size_t line = 1;
    size_t column = 1;

public:
    Lexer(std::string text)
        : text(std::move(text))
    {
    }

    void step();

    auto skip_comment() -> Token;

    auto number() -> Token;

    auto str() -> Token;

    auto n_token(TokenType type, size_t len) -> Token;

    auto next() -> Token;
};
