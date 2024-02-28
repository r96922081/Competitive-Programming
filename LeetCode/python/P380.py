from typing import List
import random

class doubly_linked_list_node:
    def __init__(self, data):
        self.data = data
        self.prev = None
        self.next = None

class doubly_linked_list:
    def __init__(self):
        self.head = None
        self.tail = None

    def append(self, data):
        new_node = doubly_linked_list_node(data)
        if not self.head:
            self.head = new_node
            self.tail = new_node
        else:
            new_node.prev = self.tail
            self.tail.next = new_node
            self.tail = new_node

    def prepend(self, data):
        new_node = doubly_linked_list_node(data)
        if not self.head:
            self.head = new_node
            self.tail = new_node
        else:
            new_node.next = self.head
            self.head.prev = new_node
            self.head = new_node

    def delete_by_node(self, node: doubly_linked_list_node):
        if node == self.head:
            self.head = node.next
        if node == self.tail:
            self.tail = node.prev
        if node.prev:
            node.prev.next = node.next
        if node.next:
            node.next.prev = node.prev

    def delete_by_data(self, data):
        n = self.find(data)
        if n:
            self.delete_by_node(n)

    def find(self, data):
        current = self.head
        while current:
            if current.data == data:
                return current
            current = current.next
        return None

    def print_list(self):
        current = self.head
        while current:
            print(current.data, end=" ")
            current = current.next
        print()


class RandomizedSet:


    def __init__(self):
        # prime that not close to power of 2
        self.key = 6091
        self.bucket = [doubly_linked_list()] * self.key
        self.non_empty_list = doubly_linked_list()
        print('hi')
        

    def insert(self, val: int) -> bool:
        list = self.bucket[val % 6091]
        if list.head == None:
            if random.randint(0, 1):
                self.non_empty_list.append(list)
            else:
                self.non_empty_list.prepend(list)
        if random.randint(0, 1):
            list.append(val)
        else:
            list.prepend(val)

    def remove(self, val: int) -> bool:
        list = self.bucket[val % 6091]
        list.delete_by_data(val)
        

    def getRandom(self) -> int:
        pass
        

obj = RandomizedSet()
param_1 = obj.insert(1)
param_3 = obj.getRandom()
param_2 = obj.remove(1)