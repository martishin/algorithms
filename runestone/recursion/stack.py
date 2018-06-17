#!/usr/bin/env python3

class Stack:
    def __init__(self):
        self.items = []

    def isEmpty(self):
        return self.items == []

    def isFull(self):
        return self.items != []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        return self.items.pop()

    def peek(self):
        return self.items[len(self.items) - 1]

    def size(self):
        return len(self.items)

def revstring(Str):
    s = Stack()
    l = len(Str)
    for i in Str:
        s.push(i)
    Str = []
    for i in range(l):
        Str.append(s.pop())
    Str = ''.join(Str)
    return Str
