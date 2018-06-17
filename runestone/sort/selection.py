#!/usr/bin/env python

def selection_sort(alist):
    for slot in range(len(alist) - 1, 0, -1):
        max_pos = 0
        for loc in range(1, slot + 1):
            if alist[loc] > alist[max_pos]:
                max_pos = loc

        tmp = alist[slot]
        alist[slot] = alist[max_pos]
        alist[max_pos] = tmp

alist = [54,26,93,17,77,31,44,55,20]
selection_sort(alist)
print(alist)