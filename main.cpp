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

   auto parser = Parser(text);
   auto tree = parser.parse();
   std::string idx0 = "phoneNumbers";
   std::string idx1 = "type";
   std::string type = tree[idx0][1][idx1];
   std::cout << type << "\n";
}
