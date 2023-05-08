import re # regular expressions

################################################################################
# tokenize input
def tokenize(input_str):
    token_specification = [
        #('NUMBER', r'\d+(\.\d*)?'),  # Integer or decimal number
        ('FLOAT', r'\d+\.\d*'),      # Decimal number
        ('INTEGER', r'\d+'),         # Integer number
        ('OP', r'[+\-*/]'),          # Arithmetic operators
        ('SKIP', r'\s+'),            # Skip over spaces and tabs
    ]

    tok_regex = '|'.join('(?P<%s>%s)' % pair for pair in token_specification)

    # list of (token class, lexeme) pairs
    return [(m.lastgroup, m.group()) for m in re.finditer(tok_regex, input_str) if m.lastgroup != 'SKIP']
    # This line of code is a list comprehension that returns a list of tuples, where each tuple contains two elements: the name of the last matched group and the corresponding matched string. The list comprehension iterates over the matches found by the `re.finditer` function when it scans the `input_str` using the `tok_regex` pattern.

    # Here's a breakdown of the list comprehension:

    # 1. `re.finditer(tok_regex, input_str)` iterates over all matches found in `input_str` using the regular expression pattern `tok_regex`.

    # 2. `m` is a match object for each match found in the input string. The match object has two important methods:
    #    - `m.lastgroup`: Returns the name of the last matched group in the regex pattern, such as 'FLOAT', 'INTEGER', 'OP', or 'SKIP'.
    #    - `m.group()`: Returns the actual matched string from the input string.

    # 3. `if m.lastgroup != 'SKIP'` is a filtering condition. It ensures that the list comprehension only includes matches whose group name is not 'SKIP'. This helps to ignore whitespace characters, as the 'SKIP' group in the regex pattern is designed to match spaces and tabs.

    # 4. `(m.lastgroup, m.group())` creates a tuple with two elements: the name of the matched group and the corresponding matched string.

    # The final result is a list of tuples that represent the token types and their corresponding values, excluding any whitespace tokens.

    # tokens = []
    # for m in re.finditer(tok_regex, input_str):
    #     if m.lastgroup != 'SKIP':
    #         value = m.group()
    #         if m.lastgroup == 'FLOAT' or m.lastgroup == 'INTEGER':
    #             tokens.append(m.lastgroup, value)
    #         else:
    #             tokens.append('UNKNOWN', value)
    # return tokens
