#!/usr/bin/env python3


# def bubble_sort(alist):
#     for num in range(len(alist) - 1, 0, -1):
#         for i in range(num):
#             if alist[i] > alist[i + 1]:
#                 temp = alist[i]
#                 alist[i] = alist[i + 1]
#                 alist[i + 1] = temp

def bubble_sort2(alist):
    for i in range(len(alist) - 1):
        for j in range(len(alist) - i - 1):
            if alist[j] > alist[j + 1]:
                alist[j], alist[j + 1] = alist[j + 1], alist[j]

def short_bubble_sort(alist):
    exc = True
    num = len(alist) - 1
    while num > 0 and exc:
        exc = False
        for i in range(num):
            if alist[i] > alist[i + 1]:
                exc = True
                tmp = alist[i]
                alist[i] = alist[i + 1]
                alist[i + 1] = tmp
        num  = num - 1

alist = [54, 26, 93, 17, 77, 31, 44, 55, 20]
short_bubble_sort(alist)
print(alist)
