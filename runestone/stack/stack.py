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

#    def push(self, item):
#        self.items.insert(0, item)

    def pop(self):
        return self.items.pop()

#    def pop(self):
#        return self.items.pop(0)

#    def peek(self):
#        return self.items[0]

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


def main():
    Str = 'Hello world'
    print(revstring(Str))
#    s = Stack()
#    print(s.isEmpty())
#    s.push(4)
#    s.push('dog')
#    print(s.peek())
#    s.push(True)
#    print(s.size())
#    print(s.isEmpty())
#    s.push(8.4)
#    print(s.pop())
#    print(s.pop())
#    print(s.size())

if __name__ == "__main__":
    main()
