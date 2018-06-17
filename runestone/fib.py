#!/usr/bin/env python3

## Example 1: Using looping technique
def fib(n):
    a, b = 1, 1
    for i in range(n - 1):
        a, b = b, a + b
    return a

print (fib(200))

## Example 2: Using recursion
def fibR(n):
    if n == 1 or n == 2:
        return 1
    return fib(n - 1) + fib(n - 2)

print (fibR(200))
