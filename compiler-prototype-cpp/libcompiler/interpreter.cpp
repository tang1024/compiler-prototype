#include <iostream>
#include <map>

#include "libcompiler/interpreter.hpp"
#include "libcompiler/parser.hpp"

#include <string>
#include <variant>

using Value = std::variant<int, std::string>;

class Environment {
public:
  void add_variable(const std::string &name, const Value &value,
                    bool is_mutable = false) {
    variables[name] = {value, is_mutable};
  }

  Value get_variable(const std::string &name) const {
    auto it = variables.find(name);
    if (it == variables.end()) {
      throw std::runtime_error("Variable not found: " + name);
    }
    return it->second.first;
  }

  void set_variable(const std::string &name, const Value &value) {
    auto it = variables.find(name);
    if (it == variables.end()) {
      throw std::runtime_error("Variable not found: " + name);
    }
    if (!it->second.second) {
      throw std::runtime_error("Cannot assign to immutable variable: " + name);
    }
    it->second.first = value;
  }

private:
  std::map<std::string, std::pair<Value, bool>> variables;
};

Value interpret_expression(const Node &node, Environment &env) {
  if (node.type == NodeType::Integer) {
    return std::stoi(node.value);
  }

  if (node.type == NodeType::StringLiteral) {
    return node.value;
  }

  if (node.type == NodeType::Identifier) {
    return env.get_variable(node.value);
  }

  if (node.type == NodeType::Add) {
    const auto &lhs = interpret_expression(node.children[0], env);
    const auto &rhs = interpret_expression(node.children[1], env);

    if (std::holds_alternative<int>(lhs) && std::holds_alternative<int>(rhs)) {
      return std::get<int>(lhs) + std::get<int>(rhs);
    }

    if (std::holds_alternative<std::string>(lhs) &&
        std::holds_alternative<std::string>(rhs)) {
      return std::get<std::string>(lhs) + std::get<std::string>(rhs);
    }

    throw std::runtime_error("Invalid types for addition operation");
  }

  throw std::runtime_error("Unknown expression type");
}

void interpret_println(const Node &node, Environment &env) {
  std::string format_string =
      std::get<std::string>(interpret_expression(node.children[0], env));
  std::vector<Value> values;

  for (size_t i = 1; i < node.children.size(); ++i) {
    values.push_back(interpret_expression(node.children[i], env));
  }

  size_t placeholder_pos = format_string.find("{}");
  size_t value_index = 0;
  while (placeholder_pos != std::string::npos && value_index < values.size()) {
    std::string value_str;
    if (std::holds_alternative<int>(values[value_index])) {
      value_str = std::to_string(std::get<int>(values[value_index]));
    } else if (std::holds_alternative<std::string>(values[value_index])) {
      value_str = std::get<std::string>(values[value_index]);
    }

    format_string.replace(placeholder_pos, 2, value_str);
    placeholder_pos =
        format_string.find("{}", placeholder_pos + value_str.size());
    ++value_index;
  }

  std::cout << format_string << std::endl;
}

void interpret_assignment(const Node &node, Environment &env) {
  if (node.type != NodeType::Assignment) {
    return;
  }

  if (node.children.empty()) {
    return;
  }

  Value value = interpret_expression(node.children[0], env);
  env.set_variable(node.value, value);
}

void interpret_let(const Node &node, Environment &env) {
  if (node.type != NodeType::Let) {
    return;
  }

  if (node.children.empty()) {
    return;
  }

  Value value = interpret_expression(node.children[0], env);
  env.add_variable(node.value, value);
}

void interpret_let_mut(const Node &node, Environment &env) {
  if (node.type != NodeType::LetMut) {
    return;
  }

  // if (node.children.empty()) {
  //   return;
  // }

  // dummy node
  auto nd = Node{NodeType::Integer, "0", std::vector<Node>{}};

  // value == 0
  Value value = interpret_expression(nd, env);

  // node.value == "res"
  env.add_variable(node.value, value, true);
}

void interpret(const Node &root_node) {
  Environment env;

  for (const Node &child : root_node.children) {
    switch (child.type) {
    case NodeType::Let:
      interpret_let(child, env);
      break;
    case NodeType::LetMut:
      interpret_let_mut(child, env);
      break;
    case NodeType::Assignment:
      interpret_assignment(child, env);
      break;
    case NodeType::Println:
      interpret_println(child, env);
      break;
    default:
      break;
    }
  }
}


