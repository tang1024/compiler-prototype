import inspect
import ast

def sample_function(a, b):
    return a * b

# Get the source code of the function as a string
function_code = inspect.getsource(sample_function)

# Parse the source code into an AST
function_ast = ast.parse(function_code)
function_ast = function_ast.body[0]

# remove the child node `args`
function_ast.args = None

# generator iterator to a list
#print({type(ast.iter_child_nodes).__name__})
children = list(ast.iter_child_nodes(function_ast))

num_child = len(children)
print(f"number of children: {num_child}")

# print child nodes
# !!!will ignore None!!!
for i, child in enumerate(children):
    print(f"child {i}: {type(child).__name__}")

# print the AST
# !!!won't ignore None!!!
print(ast.dump(function_ast, annotate_fields=True, include_attributes=False, indent=4))

# OUTPUT:
# Module(
#     body=[
#         FunctionDef(
#             name='sample_function',
#             args=arguments(
#                 posonlyargs=[],
#                 args=[
#                     arg(arg='a'),
#                     arg(arg='b')],
#                 kwonlyargs=[],
#                 kw_defaults=[],
#                 defaults=[]),
#                 Return(
#                     value=BinOp(
#                         left=Name(id='a', ctx=Load()),
#                         op=Mult(),
#                         right=Name(id='b', ctx=Load())))],
#             decorator_list=[])],
#     type_ignores=[])

# ** Process exited - Return Code: 0 **
# Press Enter to exit terminal
