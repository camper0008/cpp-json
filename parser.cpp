#include "parser.hpp"
#include <cstddef>
#include <map>
#include <optional>
#include <string>
#include <utility>

auto Parser::parse_object_field() -> std::pair<std::string, Node>
{
   auto key = lexer.next();
   switch (key.type) {
      case TokenType::String: {
         auto colon = lexer.next();
         if (colon.type != TokenType::Colon) {
            throw UnexpectedToken("NOT :", "object field");
         };
         auto value = Parser::parse();

         std::string key_node = parse_value(key);
         auto pair = std::make_pair(key_node, value);
         return { pair };
      }
      case TokenType::RBrace:
         throw UnexpectedToken("}", "object field");
      case TokenType::LBrace:
         throw UnexpectedToken("{", "object field");
      case TokenType::RBracket:
         throw UnexpectedToken("]", "object field");
      case TokenType::LBracket:
         throw UnexpectedToken("[", "object field");
      case TokenType::Int:
         throw UnexpectedToken("int", "object field");
      case TokenType::Decimal:
         throw UnexpectedToken("decimal", "object field");
      case TokenType::Colon:
         throw UnexpectedToken(":", "object field");
      case TokenType::Comma:
         throw UnexpectedToken(",", "object field");
      case TokenType::True:
         throw UnexpectedToken("true", "object field");
      case TokenType::False:
         throw UnexpectedToken("false", "object field");
      case TokenType::Null:
         throw UnexpectedToken("null", "object field");
      case TokenType::Eof:
         throw UnexpectedToken("EOF", "object field");
   }
}

auto Parser::parse_object() -> Node
{
   // current = {
   auto map = std::unordered_map<std::string, Node> {};
   while (true) {
      auto next_field = parse_object_field();
      auto key = next_field.first;
      auto value = next_field.second;
      map.emplace(key, value);

      auto next_token = lexer.next();
      if (next_token.type == TokenType::RBrace) {
         break;
      }
      if (next_token.type != TokenType::Comma) {
         throw UnexpectedToken("NOT ,", "object");
      }
   }
   return { NodeType::Object, NodeVariantType { map } };
};

auto Parser::parse_array() -> Node
{
   // current = [
   auto array = std::vector<Node> {};
   while (true) {
      auto next = parse();
      array.emplace_back(next);

      auto next_token = lexer.next();
      if (next_token.type == TokenType::RBracket) {
         break;
      }
      if (next_token.type != TokenType::Comma) {
         throw UnexpectedToken("NOT ,", "array");
      }
   }
   return { NodeType::Array, NodeVariantType { array } };
};
auto Parser::parse_value(Token token) -> Node
{
   switch (token.type) {
      case TokenType::Int: {
         auto int_text = text.substr(token.position, token.length);
         int64_t integer = std::stoi(int_text);
         return { NodeType::Int, NodeVariantType { integer } };
      }
      case TokenType::Decimal: {
         auto decimal_text = text.substr(token.position, token.length);
         double decimal = std::stod(decimal_text);
         return { NodeType::Double, NodeVariantType { decimal } };
      }
      case TokenType::String: {
         auto string_text = text.substr(token.position + 1, token.length - 2);
         return { NodeType::String, NodeVariantType { string_text } };
      }
      case TokenType::True: {
         return { NodeType::Bool, NodeVariantType { true } };
      }
      case TokenType::False: {
         return { NodeType::Bool, NodeVariantType { false } };
      }
      case TokenType::Null: {
         return { NodeType::Null, NodeVariantType { NULL } };
      }

      case TokenType::Colon:
         throw UnexpectedToken(":", "value");
      case TokenType::Comma:
         throw UnexpectedToken(",", "value");
      case TokenType::Eof:
         throw UnexpectedToken("EOF", "value");
      case TokenType::RBrace:
         throw UnexpectedToken("{", "value");
      case TokenType::LBrace:
         throw UnexpectedToken("}", "value");
      case TokenType::RBracket:
         throw UnexpectedToken("[", "value");
      case TokenType::LBracket:
         throw UnexpectedToken("]", "value");
   }
};

auto Parser::parse() -> Node
{
   auto next = lexer.next();

   switch (next.type) {
      case TokenType::LBrace:
         return parse_object();
      case TokenType::RBrace:
         throw UnexpectedToken("}", "top-level");
      case TokenType::LBracket:
         return parse_array();
      case TokenType::RBracket:
         throw UnexpectedToken("]", "top-level");
      case TokenType::Int:
      case TokenType::True:
      case TokenType::False:
      case TokenType::Decimal:
      case TokenType::String:
      case TokenType::Null:
         return parse_value(next);
      case TokenType::Colon:
         throw UnexpectedToken(":", "top-level");
      case TokenType::Comma:
         throw UnexpectedToken(",", "top-level");
      case TokenType::Eof:
         return { NodeType::Null, NodeVariantType { NULL } };
   }
};
