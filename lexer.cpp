#include "lexer.hpp"
#include <iostream>

void Lexer::step()
{
   auto current = text[this->position];
   if (current == '\n') {
      this->line++;
      this->column = 1;
   }
   else {
      this->column++;
   }
   this->position++;
}

auto Lexer::number() -> Token
{
   auto current_position = this->position;
   auto current_column = this->column;
   auto current_line = this->line;
   auto is_decimal = false;
   size_t len = 1;
   step();
   while (
      (text[this->position] >= '0' && text[this->position] <= '9') || text[this->position] == '.') {
      auto current = text[this->position];
      if (current == '.') {
         is_decimal = true;
      }
      len++;
      step();
   }

   auto token = Token {
      is_decimal ? TokenType::Decimal : TokenType::Int,
      current_position,
      len,
      current_line,
      current_column,
   };

   return token;
}

auto Lexer::str() -> Token
{
   auto current_position = this->position;
   auto current_column = this->column;
   auto current_line = this->line;
   auto is_escaped = false;
   size_t len = 1;
   step();
   while (text[this->position] != '"' || is_escaped) {
      auto current = text[this->position];
      if (is_escaped) {
         is_escaped = false;
      }
      else if (current == '\\') {
         is_escaped = true;
      }
      len++;
      step();
   }
   len++;
   step();

   auto token = Token {
      TokenType::String,
      current_position,
      len,
      current_line,
      current_column,
   };

   return token;
}

auto Lexer::n_token(TokenType type, size_t len) -> Token
{
   auto current_position = this->position;
   auto current_column = this->column;
   auto current_line = this->line;
   for (size_t i = 0; i < len; i++) {
      step();
   }

   auto token = Token {
      type,
      current_position,
      len,
      current_line,
      current_column,
   };

   return token;
}

auto Lexer::skip_comment() -> Token
{
   while (text[this->position] != '\n') {
      step();
   }
   return next();
}

auto Lexer::next() -> Token
{
   if (position >= text.length()) {
      return n_token(TokenType::Eof, 0);
   }
   auto current = text[this->position];
   switch (current) {
      case '{':
         return n_token(TokenType::LBrace, 1);
      case '}':
         return n_token(TokenType::RBrace, 1);
      case '[':
         return n_token(TokenType::LBracket, 1);
      case ']':
         return n_token(TokenType::RBracket, 1);
      case ':':
         return n_token(TokenType::Colon, 1);
      case ',':
         return n_token(TokenType::Comma, 1);
      case '\n':
      case ' ':
      case '\t': {
         step();
         return next();
      }
      case 'n': {
         std::string text_repr = "null";
         return n_token(TokenType::Null, text_repr.length());
      }
      case 'f': {
         std::string text_repr = "false";
         return n_token(TokenType::False, text_repr.length());
      }
      case 't': {
         std::string text_repr = "true";
         return n_token(TokenType::True, text_repr.length());
      }
      case '/': {
         return skip_comment();
      }

      case '"': {
         return str();
      }
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9': {
         return number();
      }
      default: {
         std::cout << "[LEXER] unrecognized character: " << current << "\n";
         std::exit(1);
      };
   }
}
