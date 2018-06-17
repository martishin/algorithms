#!/usr/bin/env python3

def anagramSolution1(s1,st2):#find exact letter in \
        #second string and delete it
    s2 = list(st2)
    i = 0
    ok = True
    while i < len(s1) and ok:
        j = 0
        found = False
        while i < len(s2) and not found:
            if s1[i] == s2[j]:
                found = True
            else:
                i += 1
        if found:
            s2[j] = None
        else:
            ok = False
        i += 1
    return ok

def anagramSolution2(st1, st2): #first we sort arrays\
        #and then we compare them
    s1 = list(st1)
    s2 = list(st2)
    s1.sort()
    s2.sort()
    pos = 0
    matches = True
    while pos < len(s1) and matches:
        if s1[pos] == s2[pos]:
            pos += 1
        else:
            matches = False
    return matches

def anagramSolution4(s1, s2):
    c1 = [0] * 26
    c2 = [0] * 26
    for i in range(len(s1)):
        pos = ord(s1[i]) - ord('a')
        c1[pos] = c1[pos] + 1
    for i in range(len(s1)):
        pos = ord(s1[i]) - ord('a')
        c2[pos] = c2[pos] + 1
    j = 0
    stillOK = True
    while j < 26 and stillOK:
        #print(c1[j], c2[j])
        if c1[j] == c2[j]:
            j = j + 1
        else:
            stillOK = False
    return stillOK

print(anagramSolution4('abcd','dcba'))
