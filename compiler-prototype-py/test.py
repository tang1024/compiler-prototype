import compiler

# Example:
input_str = "2.5 * (3 + 4) / 5"

tokens = compiler.tokenize(input_str)

ast = compiler.parse(tokens)

# ast
print("AST:")
compiler.print_ast(ast)

# codegen
print("expression:")
print(ast)
