#include "parser.hpp"
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

   using namespace std::string_literals;

   auto parser = Parser(text);
   auto tree = parser.parse();
   std::string type = tree["phoneNumbers"s][1]["type"s];
   std::cout << type << "\n"; // "office"
}
