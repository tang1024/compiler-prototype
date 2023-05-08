#pragma once

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

enum class NodeType {
  Function,
  Let,
  LetMut,
  Assignment,
  Identifier,
  Integer,
  StringLiteral,
  Add,
  Println
};

struct Node {
  NodeType type;
  std::string value;
  std::vector<Node> children;
};

using ParseResult = std::optional<Node>;

ParseResult parse_function(std::vector<Token> &tokens, size_t &pos);
ParseResult parse_let(std::vector<Token> &tokens, size_t &pos);
ParseResult parse_let_mut(std::vector<Token> &tokens, size_t &pos);
ParseResult parse_expression(std::vector<Token> &tokens, size_t &pos);
ParseResult parse_primary(std::vector<Token> &tokens, size_t &pos);
ParseResult parse_println(std::vector<Token> &tokens, size_t &pos);

void print_ast(const Node &node, int indent = 0, bool is_last_child = false);
