################################################################################
# define AST nodes (!!!without using Python ast module!!!)
class ASTNode:
    def __init__(self):
        self.children = [] # using a list

    def add_child(self, child):
        self.children.append(child)

    def remove_child(self, child):
        self.children.remove(child)

class ExprBinary(ASTNode):
    def __init__(self, left=None, op=None, right=None):
        super().__init__()
        if left is not None:
            self.add_child(left)
        self.op = op
        if right is not None:
            self.add_child(right)

    # for print()
    def __repr__(self):
        return f"({self.left} {self.op} {self.right})"
        
    @property
    def left(self):
        return self.children[0] if len(self.children) > 0 else None

    @left.setter
    def left(self, value):
        if len(self.children) > 0:
            self.children[0] = value
        else:
            self.add_child(value)

    @property
    def right(self):
        return self.children[1] if len(self.children) > 1 else None

    @right.setter
    def right(self, value):
        if len(self.children) > 1:
            self.children[1] = value
        elif len(self.children) == 1:
            self.add_child(value)
        else:
            raise IndexError("Cannot set right child without a left child")

# class Number(ASTNode):
#     def __init__(self, value, is_float):
#         self.value = value

class LiteralFloat(ASTNode):
    def __init__(self, value):
        super().__init__()
        self.value = value

    # for print()
    def __repr__(self):
        return str(self.value)

class LiteralInteger(ASTNode):
    def __init__(self, value):
        super().__init__()
        self.value = value

    # for print()
    def __repr__(self):
        return str(self.value)

class Name(ASTNode):
    def __init__(self, id):
        super().__init__()
        self.id = id

    def __repr__(self):
        return self.id

class CallExpression(ASTNode):
    def __init__(self, name, *args, redundant_id=None):
        super().__init__()
        
        self.add_child(name)

        if redundant_id is not None:
            self.add_child(redundant_id)

        for arg in args:
            self.add_child(arg)

    def __repr__(self):
        name = self.children[0]
        args = ', '.join(repr(arg) for arg in self.children[1:])
        return f"{name}({args})"

################################################################################
# tree manipulation
def traverse_and_modify(node, target_op, new_value):
    if isinstance(node, ExprBinary):
        if node.op == target_op:
            # Modify the right child with the new_value
            node.right = new_value
        else:
            # Traverse the children
            for child in node.children:
                traverse_and_modify(child, target_op, new_value)

def remove_redundant_child(node):
    if isinstance(node, CallExpression):
        # Remove the redundant_id child from the CallExpression
        redundant_id = node.children.pop(1)
        print(f"Removed redundant child: {redundant_id}")

    for child in node.children:
        remove_redundant_child(child)

################################################################################
# example
# Create a tree representing the expression (2 + 3) * (4 - 5)
tree = ExprBinary(
    left=ExprBinary(
        left=LiteralInteger(2),
        op='+',
        right=LiteralInteger(3)
    ),
    op='*',
    right=ExprBinary(
        left=LiteralInteger(4),
        op='-',
        right=LiteralInteger(5)
    )
)

# Traverse the tree and modify the right child of the subtraction operation
traverse_and_modify(tree, target_op='-', new_value=LiteralInteger(6))

#print(tree)

################################################################################
# example
# Create a tree representing the expression sin(2 * pi)
tree2 = CallExpression(
    Name("sin"),
    ExprBinary(
        left=LiteralInteger(2),
        op='*',
        right=Name("pi")
    ),
    redundant_id="sin"
)

# Traverse the tree and remove the redundant child
remove_redundant_child(tree2)

print(tree2)
