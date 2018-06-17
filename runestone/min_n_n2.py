#!/usr/bin/env python3

import sys
import random
import time

def minN(A):
    start = time.time()
    min = A[1]
    for i in A:
        if i < min:
            min = i
    stop = time.time()
    t = stop - start
    return min, t

def minN2(A):
    start = time.time()
    min = A[1]
    for i in A:
        mint = i
        for j in A:
            if i > j:
                mint = j
        if mint < min:
            min = mint
    stop = time.time()
    t = stop - start
    return min, t

def main():
    N = int(sys.argv[1])
    A = [0] * N
#    nump = 0
#    numm = 0
    for i in range(N):
        A[i] = random.randrange(0, 100000000)
    print(minN(A))
    print(minN2(A))
#    for i in A:
#        if i >= 0:
#            nump += 1
#        else:
#            numm += 1
#    print(nump, numm)

main()
