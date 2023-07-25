#include "lexer.hpp"
#include <iostream>

auto main() -> int
{
   std::string text = R"(
    {
      "firstName": "John",
      "lastName": "Smith",
      "isAlive": true,
      "age": 27,
      "address": {
        "streetAddress": "21 2nd Street",
        "city": "New York",
        "state": "NY",
        "postalCode": "10021-3100"
      },
      "phoneNumbers": [
        {
          "type": "home",
          "number": "212 555-1234"
        },
        {
          "type": "office",
          "number": "646 555-4567"
        }
      ],
      "children": [
        "Catherine",
        "Thomas",
        "Trevor"
      ],
      "spouse": null
    })";

   auto lexer = Lexer(text);

   while (true) {
      auto next = lexer.next();
      if (next.type == TokenType::Eof) {
         break;
      }
      std::cout << "[L " << next.line << ", C " << next.column << ", I " << next.position << "] "
                << text.substr(next.position, next.length) << "\n";
   }
}
