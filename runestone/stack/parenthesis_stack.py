#!/usr/bin/env python3

from stack import *

def parCheck(Str, opens, closers):
    s = Stack()
    balanced = True
    for i in Str:
        if i in opens:
            #print(opens.index(i))
            s.push(i)
        elif i in closers:
            if s.isEmpty():
                balanced = False
                break
            else:
                if closers.index(i) != opens.index(s.peek()):
                    balanced = False
                    break
                else:
                    s.pop()
        else:
            pass
    if s.isEmpty() and balanced:
        return True
    else:
       return False

def main():
    opens = '([{'
    closers = ')]}'
    print(parCheck('{(5 + 6)} * [(7 + 8) / (4 + 3)]', opens, closers))

main()
