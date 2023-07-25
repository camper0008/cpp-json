#include "parser.hpp"
#include <format>
#include <iostream>

using namespace std::literals;

auto main() -> int
{
    std::string text = R"({
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
    auto type = std::string(tree["phoneNumbers"s][1]["type"s]);
    std::cout << std::format("please let '{}' equal 'office'\n", type);
}
