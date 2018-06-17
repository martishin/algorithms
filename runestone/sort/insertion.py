#!/sur/bin/env python

def insertion_sort(alist):
    for index in range(1, len(alist)):
        curr_val = alist[index]
        pos = index
        while pos > 0 and alist[pos - 1] > curr_val:
            alist[pos] = alist[pos - 1]
            pos = pos - 1
        alist[pos] = curr_val

alist = [54,26,93,17,77,31,44,55,20]
insertion_sort(alist)
print(alist)