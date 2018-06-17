from numpy.random import sample

values = [0, -1, 5, -2, 3]

left = 0
right = len(values) - 1

while left <= right:
    for i in range(left, right, +1):
        if values[i] > values[i + 1]:
            values[i], values[i + 1] = values[i + 1], values[i]
        else:
            i += 1
    right -= 1

    for i in range(right, left, -1):
        if values[i - 1] > values[i]:
            values[i], values[i - 1] = values[i - 1], values[i]
        else:
            i -= 1
    left += 1

print values
