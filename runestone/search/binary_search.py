#!/usr/bin/env python


def binary_search(nums, n):
    l = 0
    r = len(nums)

    while (l < r):
        m = (l + r) / 2;

        if nums[m] == n:
            return m
        elif nums[m] < n:
            l = m + 1
        else:
            r = m

    return -1


def main():
    nums = [1, 2, 3, 6, 7]
    print binary_search(nums, 4)


if __name__ == '__main__':
    main()

