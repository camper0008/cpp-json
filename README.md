# cpp-json

JSON parser in CPP, created for the purposes of ergonomic access to fields.

Lexer is incredibly naïve, with 'f' eating the next 5 characters ('false'), and with 't' and 'n' eating the next 4 ('true', 'null'), and any lone '/' found skipping until the next newline. 

This should be fixed at some point.
