import unittest


def is_palindrome(number):
    if not isinstance(number, int) or number < 0:
        raise ValueError("Входное значение должно быть неотрицательным целым числом")

    return str(number) == str(number)[::-1]
