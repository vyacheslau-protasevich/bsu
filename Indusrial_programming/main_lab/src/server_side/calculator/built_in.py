def calculate_default(expression: str):
    try:
        # Use eval to evaluate the expression
        result = eval(expression)
        print(f"Result: {result}")
    except Exception as e:
        print(f"Error: {e}")
