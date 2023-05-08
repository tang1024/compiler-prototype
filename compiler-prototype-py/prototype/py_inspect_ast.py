import inspect
import ast

def sample_function(a, b):
    return a * b

# Get the source code of the function as a string
function_code = inspect.getsource(sample_function)

# Parse the source code into an AST
function_ast = ast.parse(function_code)

# Print the AST
print(ast.dump(function_ast))

# OUTPUT:
# Module(body=[FunctionDef(name='sample_function', args=arguments(posonlyargs=[], args=[arg(arg='a', annotation=None, type_comment=None), arg(arg='b', annotation=None, type_comment=None)], vararg=None, kwonlyargs=[], kw_defaults=[], kwarg=None, defaults=[]), body=[Return(value=BinOp(left=Name(id='a', ctx=Load()), op=Mult(), right=Name(id='b', ctx=Load())))], decorator_list=[], returns=None, type_comment=None)], type_ignores=[])

# ** Process exited - Return Code: 0 **
# Press Enter to exit terminal
