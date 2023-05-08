#include <algorithm>
#include <cassert>
#include <cctype>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <string>
#include <vector>

#include "libcompiler/lexer.hpp"
#include "libcompiler/parser.hpp"

ParseResult parse_assignment(std::vector<Token> &tokens, size_t &pos) {
  if (tokens[pos].type != TokenType::Ident) {
    return std::nullopt;
  }
  std::string ident = tokens[pos].value;
  ++pos;

  if (tokens[pos].type != TokenType::Equals) {
    --pos;
    return std::nullopt;
  }
  ++pos;

  auto expr = parse_expression(tokens, pos);
  if (!expr) {
    return std::nullopt;
  }

  if (tokens[pos].type != TokenType::Semicolon) {
    return std::nullopt;
  }
  ++pos;

  return Node{NodeType::Assignment, ident, {expr.value()}};
}

ParseResult parse_function(std::vector<Token> &tokens, size_t &pos) {
  if (tokens[pos].type != TokenType::Fn) {
    return std::nullopt;
  }
  ++pos;

  if (tokens[pos].type != TokenType::Main) {
    return std::nullopt;
  }
  ++pos;

  if (tokens[pos].type != TokenType::ParenOpen) {
    return std::nullopt;
  }
  ++pos;

  if (tokens[pos].type != TokenType::ParenClose) {
    return std::nullopt;
  }
  ++pos;

  if (tokens[pos].type != TokenType::BraceOpen) {
    return std::nullopt;
  }
  ++pos;

  std::vector<Node> children;
  while (tokens[pos].type != TokenType::BraceClose) {
    auto let = parse_let(tokens, pos);
    if (let) {
      children.push_back(let.value());
      continue;
    }

    auto let_mut = parse_let_mut(tokens, pos);
    if (let_mut) {
      children.push_back(let_mut.value());
      continue;
    }

    auto assignment = parse_assignment(tokens, pos);
    if (assignment) {
      children.push_back(assignment.value());
      continue;
    }

    auto println = parse_println(tokens, pos);
    if (println) {
      children.push_back(println.value());
      continue;
    }

    // probably it's a '}'
    break;
  }

  if (tokens[pos].type != TokenType::BraceClose) {
    assert(false && "Expected '}'");
    return std::nullopt;
  }
  ++pos;

  return Node{NodeType::Function, "", children};
}

ParseResult parse_let(std::vector<Token> &tokens, size_t &pos) {
  if (tokens[pos].type != TokenType::Let) {
    return std::nullopt;
  }
  ++pos;

  if (tokens[pos].type != TokenType::Ident) {
    --pos;
    return std::nullopt;
  }
  std::string ident = tokens[pos].value;
  ++pos;

  if (tokens[pos].type != TokenType::Equals) {
    return std::nullopt;
  }
  ++pos;

  auto expr = parse_expression(tokens, pos);
  if (!expr) {
    return std::nullopt;
  }

  if (tokens[pos].type != TokenType::Semicolon) {
    return std::nullopt;
  }
  ++pos;

  return Node{NodeType::Let, ident, {expr.value()}};
}

ParseResult parse_let_mut(std::vector<Token> &tokens, size_t &pos) {
  if (tokens[pos].type != TokenType::Let) {
    return std::nullopt;
  }
  ++pos;

  if (tokens[pos].type != TokenType::Mut) {
    --pos;
    return std::nullopt;
  }
  ++pos;

  if (tokens[pos].type != TokenType::Ident) {
    return std::nullopt;
  }
  std::string ident = tokens[pos].value;
  ++pos;

  Node let_mut_node{NodeType::LetMut, ident, {}};

  if (tokens[pos].type == TokenType::Equals) {
    ++pos;

    auto expr = parse_expression(tokens, pos);
    if (!expr) {
      return std::nullopt;
    }

    let_mut_node.children.push_back(expr.value());
  }

  if (tokens[pos].type != TokenType::Semicolon) {
    return std::nullopt;
  }
  ++pos;

  return let_mut_node;
}

ParseResult parse_expression(std::vector<Token> &tokens, size_t &pos) {
  auto lhs = parse_primary(tokens, pos);
  if (!lhs) {
    return std::nullopt;
  }

  if (tokens[pos].type == TokenType::Plus) {
    ++pos;

    auto rhs = parse_primary(tokens, pos);
    if (!rhs) {
      return std::nullopt;
    }

    return Node{NodeType::Add, "", {lhs.value(), rhs.value()}};
  }

  return lhs;
}

ParseResult parse_primary(std::vector<Token> &tokens, size_t &pos) {
  if (tokens[pos].type == TokenType::Integer) {
    std::string value = tokens[pos].value;
    ++pos;
    return Node{NodeType::Integer, value, {}};
  }

  if (tokens[pos].type == TokenType::StringLiteral) {
    std::string value = tokens[pos].value;
    ++pos;
    return Node{NodeType::StringLiteral, value, {}};
  }

  if (tokens[pos].type == TokenType::Ident) {
    std::string value = tokens[pos].value;
    ++pos;
    return Node{NodeType::Identifier, value, {}};
  }

  return std::nullopt;
}

ParseResult parse_println(std::vector<Token> &tokens, size_t &pos) {
  if (tokens[pos].type != TokenType::Println) {
    return std::nullopt;
  }
  ++pos;

  if (tokens[pos].type != TokenType::Exclamation) {
    return std::nullopt;
  }
  ++pos;

  if (tokens[pos].type != TokenType::ParenOpen) {
    return std::nullopt;
  }
  ++pos;

  std::vector<Node> children;
  while (tokens[pos].type != TokenType::ParenClose) {
    auto expr = parse_expression(tokens, pos);
    if (!expr) {
      return std::nullopt;
    }
    children.push_back(expr.value());

    if (tokens[pos].type == TokenType::Comma) {
      ++pos;
    } else if (tokens[pos].type != TokenType::ParenClose) {
      return std::nullopt;
    }
  }

  if (tokens[pos].type != TokenType::ParenClose) {
    return std::nullopt;
  }
  ++pos;

  if (tokens[pos].type != TokenType::Semicolon) {
    return std::nullopt;
  }
  ++pos;

  return Node{NodeType::Println, "", children};
}

// print functions

void print_ast(const Node &node, int indent, bool is_child) {
  std::string indent_str(indent, ' ');

  if (is_child) {
    indent_str = indent_str.substr(0, indent_str.size() - 2) + "└─";
  }

  switch (node.type) {
  case NodeType::Function:
    std::cout << indent_str << "Function(main)\n";
    break;
  case NodeType::Let:
    std::cout << indent_str << "Let(" << node.value << ")\n";
    break;
  case NodeType::LetMut:
    std::cout << indent_str << "LetMut(" << node.value << ")\n";
    break;
  case NodeType::Identifier:
    std::cout << indent_str << "Identifier(" << node.value << ")\n";
    break;
  case NodeType::Integer:
    std::cout << indent_str << "Integer(" << node.value << ")\n";
    break;
  case NodeType::StringLiteral:
    std::cout << indent_str << "StringLiteral(\"" << node.value << "\")\n";
    break;
  case NodeType::Add:
    std::cout << indent_str << "Add\n";
    break;
  case NodeType::Println:
    std::cout << indent_str << "Println\n";
    break;
  case NodeType::Assignment:
    std::cout << indent_str << "Assignment\n";
    break;
  default:
    assert(false);
  }

  for (size_t i = 0; i < node.children.size(); ++i) {
    print_ast(node.children[i], indent + 2, true);
  }
}
