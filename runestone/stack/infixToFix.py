#!/usr/bin/env python3

from stack import *
import sys
import pdb

def infixToPostfix(in_str):
    signs = {}
    signs['*'] = 3
    signs['/'] = 3
    signs['+'] = 2
    signs['-'] = 2
    signs['('] = 1

    stack = Stack()
    postfixList = []
    tokenList = in_str.split()

    for token in tokenList:
        if token in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ' or token in '0123456789':
            postfixList.append(token)
        elif token == '(':
            stack.push(token)
        elif token == ')':
            topToken = stack.pop()
            while topToken != '(':
                postfixList.append(topToken)
                topToken = stack.pop()
        else:
            while (not stack.isEmpty()) and (signs[stack.peek()] >= signs[token]):
                postfixList.append(stack.pop())
            stack.push(token)

    while not stack.isEmpty():
        postfixList.append(stack.pop())

    return ' '.join(postfixList)


def postfixEval(postfixExpr):
    operandStack = Stack()
    tokenList = postfixExpr.split()

    for token in tokenList:
        if token in '0123456789':
            operandStack.push(int(token))
        else:
            operand2 = operandStack.pop()
            operand1 = operandStack.pop()
            result = doMath(token, operand1, operand2)
            operandStack.push(result)

    return operandStack.pop()


def doMath(op, op1, op2):
    if op == '*':
        return op1 * op2
    elif op == '/':
        return op1 / op2
    elif op == '+':
        return op1 + op2
    else:
        return op1 - op2

print(postfixEval('7 8 + 3 2 + /'))
#print(infixToPostfix(sys.argv[1]))

