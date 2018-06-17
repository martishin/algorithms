#!/usr/bin/env python3

from deque import *

def palchecker(string):
    deque = Deque()

    for char in string:
        deque.addRear(char)

    stillEqual = True

    while deque.size() > 1 and stillEqual:
        first = deque.removeFront()
        last = deque.removeRear()
        if first != last:
            stillEqual = False

    return stillEqual

print('alsdkjfskf -', palchecker('lsdkjfskf'))
print('radar -', palchecker('radar'))
