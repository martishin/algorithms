#!/usr/bin/env python3

from stack import *
import sys

def baseConvert(dNum, base):
    digits = '0123456789ABCDEF'
    stack = Stack()
    result = ''

    while dNum > 0:
        stack.push(dNum % base)
        dNum //= base

    while stack.isFull():
        result += digits[stack.pop()]

    return result


def binaryConvert(dNum):
    stack = Stack()
    result = ''
    if dNum == 0:
        result += '0'

    else:
        while dNum > 0:
            stack.push(dNum % 2)
            dNum //= 2
        while stack.isFull():
            result += str(stack.pop())

    return result


def decimalConvert(bNum):
    a = [i for i in str(bNum)]
    result = 0

    for i in range(len(a)):
        result += (int(a[i]) * (2 ** (len(a) - i - 1)))

    return result


#for i in range(100):
#    print((binaryConvert(i), decimalConvert(binaryConvert(i))))
#print(binaryConvert(25))
#print(baseConvert(25, 2))
print(baseConvert(int(sys.argv[1]), int(sys.argv[2])))

