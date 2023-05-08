from .ast import *

################################################################################
# parsing functions
def _parse_expression(tokens):
    left, remaining_tokens = _parse_term(tokens)

    while remaining_tokens and remaining_tokens[0][0] == 'OP' and remaining_tokens[0][1] in ['+', '-']:
        op = remaining_tokens.pop(0)[1]
        right, remaining_tokens = _parse_term(remaining_tokens)
        left = ExprBinary(left, op, right)

    return left, remaining_tokens

def _parse_term(tokens):
    left, remaining_tokens = _parse_factor(tokens)

    while remaining_tokens and remaining_tokens[0][0] == 'OP' and remaining_tokens[0][1] in ['*', '/']:
        op = remaining_tokens.pop(0)[1]
        right, remaining_tokens = _parse_factor(remaining_tokens)
        left = ExprBinary(left, op, right)

    return left, remaining_tokens

def _parse_factor(tokens):
    if not tokens:
        raise ValueError("Unexpected end of input")

    token, value = tokens.pop(0)
    if token == 'FLOAT':
        return LiteralFloat(float(value)), tokens
    elif token == 'INTEGER':
        return LiteralInteger(int(value)), tokens
    else:
        raise ValueError(f"Unexpected token: {token}")

################################################################################
# public api
def parse(tokens):
    ast, remaining_tokens = _parse_expression(tokens)

    if remaining_tokens:
        raise ValueError(f"Unexpected token: {remaining_tokens[0][0]}")
        
    return ast
