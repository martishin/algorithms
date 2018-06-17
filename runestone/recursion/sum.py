#!/usr/bin/env python

def listsum(num_list):
    if len(num_list) == 1:
        return num_list[0]
    else:
        return num_list[0] + listsum(num_list[1:])

print(listsum([1,3,5,7,9]))
