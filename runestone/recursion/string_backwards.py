#!/usr/bin/env python

import sys

def stringBackwards(input_string):
    input_array = list(input_string)
    try:
        return input_array.pop() + stringBackwards(input_array)
    except Exception:
        return ''

print(stringBackwards(sys.argv[1]))
