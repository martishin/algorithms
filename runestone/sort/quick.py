#!/usr/bin/env python


import random


def partition(nums, l, r, p):
    nums[p], nums[l] = nums[l], nums[p]
    p = l;

    for i in range(l + 1, r):
        if nums[i] <= nums[l]:
            p += 1;
            nums[i], nums[p] = nums[p], nums[i]

    nums[l], nums[p] = nums[p], nums[l]
    return p


def quicksort(nums, l, r):
    if l < r:
        p = l + random.randint(0, r - l - 1)
        p = partition(nums, l, r, p)

        quicksort(nums, l, p)
        quicksort(nums, p + 1, r)


def main():
    nums = [1, 3, 2, 6, 5, 7]
    quicksort(nums, 0, len(nums))
    print nums


if __name__ == '__main__':
    main()

