################################################################################
# define AST nodes
class ASTNode:
    pass

class ExprBinary(ASTNode):
    def __init__(self, left, op, right):
        self.left = left
        self.op = op
        self.right = right

    # for print()
    def __repr__(self):
        return f"({self.left} {self.op} {self.right})"

# class Number(ASTNode):
#     def __init__(self, value, is_float):
#         self.value = value

class LiteralFloat(ASTNode):
    def __init__(self, value):
        self.value = value

    # for print()
    def __repr__(self):
        return str(self.value)

class LiteralInteger(ASTNode):
    def __init__(self, value):
        self.value = value

    # for print()
    def __repr__(self):
        return str(self.value)

################################################################################
# pretty print
def print_ast(node, branches=None):
    if branches is None:
        branches = []

    def print_branches(branches):
        for i in range(len(branches)):
            if i != len(branches) - 1:
                print("│   " if branches[i] else "    ", end="")
            else:
                print("├── " if branches[i] else "└── ", end="")

    print_branches(branches)

    if isinstance(node, LiteralFloat):
        print(f"LiteralFloat: {node.value}")
    elif isinstance(node, LiteralInteger):
        print(f"LiteralInteger: {node.value}")
    elif isinstance(node, ExprBinary):
        print(f"ExprBinary: {node.op}")
        children = [node.left, node.right]
        for i, child in enumerate(children):
            child_branches = branches.copy()
            child_branches.append(i < len(children) - 1)
            print_ast(child, child_branches)
    else:
        raise TypeError(f"Unknown node type: {type(node)}")
