#!/usr/bin/env python

def shell_sort(alist):
    sub_count = len(alist) // 2
    while sub_count > 0:
        for start_pos in range(sub_count):
            gap_insertion_sort(alist, start_pos, sub_count)

        print('After increments of size', sub_count, 'The list is', alist)
        sub_count = sub_count // 2


def gap_insertion_sort(alist, start, gap):
    for i in range(start + gap, len(alist), gap):
        curr_value = alist[i]
        pos = i

        while pos >= gap and alist[pos - gap] > curr_value:
            alist[pos] = alist[pos - gap]
            pos = pos - gap

        alist[pos] = curr_value

alist = [54,26,93,17,77,31,44,55,20]
shell_sort(alist)
print(alist)
