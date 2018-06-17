#!/usr/bin/env python3

import time

def SumN1(n):
    start = time.time()
    Sum = 0
    for i in range(1, n + 1):
        Sum = Sum + i
    end = time.time()
    return Sum, end - start

def SumN2(n):
    start = time.time()
    Sum = (n * (n + 1))/2
    end = time.time()
    return Sum, end - start

#for i in range(5):
#    print('Sum is %d required %10.7f seconds' % SumN1(100000))

a = [10000, 100000, 1000000, 10000000, 10000000]

for i in a:
    print('Sum is %d required %10.9f seconds' % SumN2(i))

