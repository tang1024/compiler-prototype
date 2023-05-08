#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <string>
#include <vector>

#include "libcompiler/lexer.hpp"

Token lex_string_literal(const std::string &input, size_t &pos) {
  std::string value;
  ++pos; // Skip the opening double quote

  while (pos < input.size() && input[pos] != '\"') {
    value += input[pos];
    ++pos;
  }

  if (pos >= input.size()) {
    throw std::runtime_error("Unterminated string literal");
  }

  ++pos; // Skip the closing double quote
  return Token{TokenType::StringLiteral, value};
}

std::vector<Token> lex(const std::string &input) {
  std::vector<Token> tokens;
  size_t pos = 0;

  auto is_whitespace = [](char c) { return std::isspace(c); };
  auto is_alpha = [](char c) { return std::isalpha(c); };
  auto is_digit = [](char c) { return std::isdigit(c); };

  while (pos < input.size()) {
    char c = input[pos];

    if (is_whitespace(c)) {
      ++pos;
      continue;
    }

    if (is_alpha(c)) {
      std::string ident;
      while (
          pos < input.size() &&
          (is_alpha(input[pos]) || is_digit(input[pos]) || input[pos] == '_')) {
        ident.push_back(input[pos++]);
      }

      if (ident == "fn") {
        tokens.push_back({TokenType::Fn, ident});
      } else if (ident == "let") {
        tokens.push_back({TokenType::Let, ident});
      } else if (ident == "mut") {
        tokens.push_back({TokenType::Mut, ident});
      } else if (ident == "main") {
        tokens.push_back({TokenType::Main, ident});
      } else if (ident == "println") {
        tokens.push_back({TokenType::Println, ident});
      } else {
        tokens.push_back({TokenType::Ident, ident});
      }
    } else if (is_digit(c)) {
      std::string num;
      while (pos < input.size() && is_digit(input[pos])) {
        num.push_back(input[pos++]);
      }
      tokens.push_back({TokenType::Integer, num});
    } else {
      switch (c) {
      case '+':
        tokens.push_back({TokenType::Plus, "+"});
        ++pos;
        break;
      case '-':
        tokens.push_back({TokenType::Minus, "-"});
        ++pos;
        break;
      case '*':
        tokens.push_back({TokenType::Asterisk, "*"});
        ++pos;
        break;
      case '/':
        tokens.push_back({TokenType::Slash, "/"});
        ++pos;
        break;
      case '=':
        tokens.push_back({TokenType::Equals, "="});
        ++pos;
        break;
      case '(':
        tokens.push_back({TokenType::ParenOpen, "("});
        ++pos;
        break;
      case ')':
        tokens.push_back({TokenType::ParenClose, ")"});
        ++pos;
        break;
      case '{':
        tokens.push_back({TokenType::BraceOpen, "{"});
        ++pos;
        break;
      case '}':
        tokens.push_back({TokenType::BraceClose, "}"});
        ++pos;
        break;
      case ';':
        tokens.push_back({TokenType::Semicolon, ";"});
        ++pos;
        break;
      case '!':
        tokens.push_back({TokenType::Exclamation, "!"});
        ++pos;
        break;
      case ',':
        tokens.push_back(Token{TokenType::Comma, ","});
        ++pos;
        break;
      case '\"':
        tokens.push_back(lex_string_literal(input, pos));
        break;
      default:
        throw std::runtime_error("Unknown character: " + std::string(1, c));
      }
    }
  }

  tokens.push_back({TokenType::Eof, ""});
  return tokens;
}
