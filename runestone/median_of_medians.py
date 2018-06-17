#!/usr/bin/env python3

import random
import sys

def select(A, k):
    if len(A) < 10:
        A.sort()
        return A[k]
    S = []
    lIndex = 0
    while lIndex+5 < len(A)-1:
        S.append(A[lIndex:lIndex+5])
        lIndex += 5
    S.append(A[lIndex:])
    Meds = []
    for subList in S:
        Meds.append(select(subList, int((len(subList)-1)/2)))
    med = select(Meds, int((len(Meds)-1)/2))
    S1 = []
    S2 = []
    S3 = []
    for i in A:
        if i < med:
            S1.append(i)
        elif i > med:
            S3.append(i)
        else:
            S2.append(i)
    if k < len(S1):
        return select(S1, k)
    elif k < len(S2) + len(S1):
        return S2[0]
    else:
        return select(S3, k-len(S1)-len(S2))

def main():
    N = int(sys.argv[1])
    k = int(sys.argv[2]) - 1
    A = [0] * N
    for i in range(N):
        A[i] = random.randrange(0, 100000)
    print(A, select(A, k))
    print(sorted(A), sorted(A)[k])

main()
