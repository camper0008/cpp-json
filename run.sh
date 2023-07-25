#!/bin/sh

clang++ $(cat compile_flags.txt) lexer.cpp parser.cpp main.cpp && ./a.out
