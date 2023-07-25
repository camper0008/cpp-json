#pragma once

#include "position.hpp"
#include <cstddef>
#include <format>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

enum class TokenType {
    Eof,
    Error,
    Id,

    Int,
    Decimal,
    String,
    True,
    False,
    Null,

    RBrace,
    LBrace,
    RBracket,
    LBracket,
    Colon,
    Comma,
};

struct Token {
    TokenType type;
    Position pos;
    size_t length;

    constexpr auto value(std::string_view text) const noexcept -> std::string
    {
        return pos.value(text, this->length);
    }
};

auto keyword_token_type(std::string& value) noexcept -> TokenType;

class Lexer {
private:
    std::string_view text;
    ErrorCollector* errors;

    size_t index = 0;
    size_t line = 1;
    size_t column = 1;

public:
    Lexer(std::string_view text, ErrorCollector* errors)
        : text(text)
        , errors(errors)
    {
    }

    auto next() -> Token;

private:
    auto lex_number() -> Token;
    auto lex_string() -> Token;
    auto lex_id() -> Token;
    auto skip_comment() -> Token;
    auto skip_whitespace() -> Token;

    constexpr void step() noexcept
    {
        if (current() == '\n') {
            this->line++;
            this->column = 1;
        }
        else {
            this->column++;
        }
        this->index++;
    }

    constexpr auto token(TokenType type, Position pos) const noexcept -> Token
    {
        return { type, pos, index - pos.index };
    }

    constexpr auto position() const noexcept -> Position
    {
        return { this->index, this->line, this->column };
    }

    constexpr auto current_is(char value) const noexcept -> bool
    {
        return not done() and current() == value;
    }

    constexpr auto done() const noexcept -> bool { return this->index >= this->text.length(); }

    constexpr auto current() const noexcept -> char { return this->text.at(this->index); }
};
