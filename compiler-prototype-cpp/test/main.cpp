#include <cctype>
#include <iostream>
#include <string>
#include <vector>

//#include "libcompiler/lexer.hpp"
//#include "libcompiler/parser.hpp"

#include <fstream>
#include <sstream>

std::string read_file(const std::string &filename) {
  std::ifstream file(filename);
  if (!file) {
    throw std::runtime_error("Unable to open file: " + filename);
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}


//int main() {
//  std::string input = read_file("../rust/main.rs");
//
//  std::vector<Token> tokens = lex(input);
//  size_t pos = 0;
//  auto ast = parse_function(tokens, pos);
//
//  if (ast) {
//    print_ast(ast.value());
//  } else {
//    std::cerr << "Parsing error\n";
//  }
//
//  return 0;
//}

#include "libcompiler/interpreter.hpp"
#include "libcompiler/lexer.hpp"
#include "libcompiler/parser.hpp"

int main() {
  std::ifstream file("../rust/main.rs");

  if (!file.is_open()) {
    std::cerr << "Error opening file." << std::endl;
    return 1;
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string source = buffer.str();

  auto tokens = lex(source);

  size_t pos = 0;
  auto root_node = parse_function(tokens, pos);

  if (root_node) {
    print_ast(root_node.value(), 0, false);
    interpret(root_node.value());
  } else {
    std::cerr << "Failed to parse the source code." << std::endl;
    return 1;
  }

  return 0;
}
