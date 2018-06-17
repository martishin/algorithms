#!/usr/bin/env python3

def bubbleSort(A):
    for i in range(len(A)):
        for j in range(i, len(A)):
            if A[i] < A[j]:
                A[i] = A[i] + A[j]
                A[j] = A[i] - A[j]
                A[i] = A[i] - A[j]
    print(A)

def main():
    bubbleSort([1, 4, 3, 2, 7])

main()
