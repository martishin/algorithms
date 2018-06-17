#!/usr/bin/env python3

class fraction:
    def __init__(self, top, bottom):
        common = gcd(top, bottom)
        self.num = top//common  #numerator
        self.den = bottom//common #denominator

    def getNum(self):
        return(self.num)

    def getDen(self):
        return(self.den)

    def show(self):
        print(self.num, "/", self.den)

    def __str__(self):
        return str(self.num) + "/" + str(self.den)

    def __eq__(self, other):
        nnum = self.num * other.den
        snum = other.num * self.den
        return nnum == snum

    def __truediv__(self, other):
        nnum = self.num * other.den
        nden = self.den * other.num
        return fraction(nnum, nden)

    def __add__(self, other):
        nnum = self.num * other.den + self.den * other.num
        nden = self.den * other.den
        return fraction(nnum, nden)

    def __mul__(self, other):
       nnum = self.num * other.num
       nden = self.den * other.den
       return fraction(nnum, nden)

    def __sub__(self, other):
        nnum = self.num * other.den - self.den * other.num
        nden = self.den * other.den
        return fraction(nnum, nden)

    def __lt__(self, other):
        nnum = self.num * other.den
        snum = other.num * self.den
        return nnum < snum

    def __gt__(self, other):
        nnum = self.num * other.den
        snum = other.num * self.den
        return nnum > snum

def gcd(m, n): #greatest common divisor
    while m % n != 0:
        om = m
        on = n
        m = on
        n = om % on
    return n

def main():
   x = fraction(1, 2)
   y = fraction(2, 3)
   z = fraction(2, 5)
   print(x.getDen())
   print(x / y)

main()
