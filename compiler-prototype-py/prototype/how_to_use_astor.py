# string to AST
# https://docs.python.org/3/library/ast.html
import ast

# AST to string
# https://github.com/berkerpeksag/astor
# install it first
import astor

# Convert Python code to an AST
source_code = """
if a < 1:
    b = 1
elif a > 3:
    b = 3
else:
    if a < 2:
        b = 2
    else:
        b = 4
"""

tree = ast.parse(source_code)

# Convert the AST back to Python code
round_tripped_code = astor.to_source(tree)

print(round_tripped_code)

# result:
# python .\demo.py
# if a < 1:
#     b = 1
# elif a > 3:
#     b = 3
# elif a < 2:
#     b = 2
# else:
#     b = 4

# The result is correct and equivalent to the original code. 

# Here's why: the `astor` library is designed to convert an Abstract Syntax Tree (AST) back into Python code. However, the formatting of the resulting code may not be the same as the original code. The goal is to produce equivalent code, not identical code.

# The nested `if` statement in your `else` clause is converted to an `elif` statement in the resulting code:

# ```python
# else:
#     if a < 2:
#         b = 2
#     else:
#         b = 4
# ```
# is converted to:
# ```python
# elif a < 2:
#     b = 2
# else:
#     b = 4
# ```
# This transformation simplifies the nested `if` statement without changing its behavior. The two code snippets are equivalent: they will behave the same way for any input. 

# The transformation from a nested `if` statement to an `elif` statement is a common way to simplify control flow in Python code. It makes the code easier to read and understand, without changing its behavior.
