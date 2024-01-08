from unittest import TestCase
from colloquium.coloc_2.block_1.palyndrom_2 import is_palindrome


class Test(TestCase):
    def test_negative_input(self):
        with self.assertRaises(ValueError):
            is_palindrome(-121)

    def test_non_integer_input(self):
        with self.assertRaises(ValueError):
            is_palindrome(12.21)

    def test_palindrome_input(self):
        self.assertTrue(is_palindrome(1221))

    def test_non_palindrome_input(self):
        self.assertFalse(is_palindrome(1234))
