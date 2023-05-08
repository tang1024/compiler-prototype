# compiler-prototype

`compiler-prototype` is a project providing simple compiler prototypes.

## compiler-prototype-py

### Components

- lexer
- parser
- AST

### Supported Expressions

- Binary Operator Expression (Arithmetic addition, subtraction, multiplication, division)
- Float Literal Expression
- Integer Literal Expression

### Example

```
> python ./py/test.py
[CompilerPrototypePy] Initializing the package...
[CompilerPrototypePy] The package is initialized.
AST:
ExprBinary: +
├── ExprBinary: *
│   ├── LiteralFloat: 2.5
│   └── LiteralInteger: 3
└── ExprBinary: /
    ├── LiteralInteger: 4
    └── LiteralInteger: 5
expression:
((2.5 * 3) + (4 / 5))
```
