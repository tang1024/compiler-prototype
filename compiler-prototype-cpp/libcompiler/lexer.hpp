#pragma once

#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

enum class TokenType {
  Fn,
  Let,
  Mut,
  Main,
  Ident,
  Integer,
  StringLiteral,
  Plus,
  Minus,
  Asterisk,
  Slash,
  Equals,
  ParenOpen,
  ParenClose,
  BraceOpen,
  BraceClose,
  Semicolon,
  Comma,
  Println,
  Exclamation,
  Eof
};

struct Token {
  TokenType type;
  std::string value;
};

std::vector<Token> lex(const std::string& input);
