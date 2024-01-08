from unittest import TestCase
from colloquium.coloc_2.block_1.fibonachi_1 import generate_fibonacci


class Test(TestCase):
    def test_negative_input(self):
        with self.assertRaises(ValueError):
            generate_fibonacci(-1)

    def test_zero_input(self):
        with self.assertRaises(ValueError):
            generate_fibonacci(0)

    def test_positive_input(self):
        self.assertEqual(generate_fibonacci(5), [0, 1, 1, 2, 3])

