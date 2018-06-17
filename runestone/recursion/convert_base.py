#!/usr/bin/env python

import sys
from stack import Stack

base_stack = Stack()

#def toStr(n,base):
#   convertString = "0123456789ABCDEF"
#   if n < base:
#      return convertString[n]
#   else:
#      return toStr(n//base,base) + convertString[n%base]

def convertToString(n, base):
    base_string = '0123456789ABCDEF'
    while n > 0:
        if n < base:
            base_stack.push(base_string[n])
        else:
            base_stack.push(base_string[n % base])
        n //= base
    result = ''
    while not base_stack.isEmpty():
        result += str(base_stack.pop())
    return result

print(convertToString(int(sys.argv[1]), int(sys.argv[2])))
