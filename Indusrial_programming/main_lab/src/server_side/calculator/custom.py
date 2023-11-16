def add(x, y):
    return x + y


def subtract(x, y):
    return x - y


def multiply(x, y):
    return x * y


def divide(x, y):
    if y != 0:
        return x / y
    else:
        raise ValueError("Cannot divide by zero.")


def parse_expression(expression):
    operators = set("+-*/")
    tokens = []
    current_token = ""

    for char in expression:
        if char.isdigit() or char == ".":
            current_token += char
        elif char in operators:
            if current_token:
                tokens.append(float(current_token))
                current_token = ""
            tokens.append(char)

    if current_token:
        tokens.append(float(current_token))

    return tokens


def calculate(tokens):
    operators = {'+': add, '-': subtract, '*': multiply, '/': divide}
    stack = []

    for token in tokens:
        if token in operators:
            if len(stack) < 2:
                raise ValueError("Invalid expression")
            y, x = stack.pop(), stack.pop()
            result = operators[token](x, y)
            stack.append(result)
        else:
            stack.append(token)

    if len(stack) != 1:
        raise ValueError("Invalid expression")

    return stack[0]


# Take user input as a string
expression = input("Enter a mathematical expression: ")

try:
    # Parse the expression and calculate the result
    tokens = parse_expression(expression)
    result = calculate(tokens)
    print(f"Result: {result}")
except Exception as e:
    print(f"Error: {e}")
