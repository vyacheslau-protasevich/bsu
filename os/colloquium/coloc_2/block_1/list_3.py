import unittest


class Node:
    def __init__(self, value):
        self.value = value
        self.next = None


def reverse_linked_list(head):
    if head is None or head.next is None:
        return head

    prev = None
    current = head
    while current is not None:
        next_node = current.next
        current.next = prev
        prev = current
        current = next_node

    return prev
