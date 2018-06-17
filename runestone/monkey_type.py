#!/usr/bin/env python3

import sys
import random
import string

def generate(s):
    b = []
    for i in range(len(s)):
        ns = ''
        for j in range(len(s[i])):
           ns = ns + random.choice(string.ascii_lowercase)
        b.append(ns)
    return b

def compare(s, b):
    for i in range(len(s)):
        if s[i] != b[i]:
            return False
            break
    return True

if __name__ == '__main__':
    s = (str(sys.argv[1])).split()
    num = 0
    while not compare(s, generate(s)):
        num += 1
    print(num)
