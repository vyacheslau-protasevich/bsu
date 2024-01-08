from unittest import TestCase
from colloquium.coloc_2.block_1.list_3 import Node, reverse_linked_list


if __name__ == "__main__":
    main()


class Test(TestCase):
    def test_empty_list(self):
        self.assertIsNone(reverse_linked_list(None))

    def test_single_node_list(self):
        head = Node(1)
        self.assertEqual(reverse_linked_list(head).value, 1)

    def test_multiple_nodes_list(self):
        head = Node(1)
        head.next = Node(2)
        head.next.next = Node(3)

        reversed_head = reverse_linked_list(head)
        self.assertEqual(reversed_head.value, 3)
        self.assertEqual(reversed_head.next.value, 2)
        self.assertEqual(reversed_head.next.next.value, 1)
