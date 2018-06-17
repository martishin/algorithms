#!/usr/bin/env python


def merge_sort(nums, l, r):
    if l < r:
        m = (l + r) / 2
        merge_sort(nums, l, m)
        merge_sort(nums, m + 1, r)
        merge(nums, l, m, r)


def merge(nums, l, m, r):
    li = 0
    ri = 0
    left_part = []
    right_part = []

    for i in range(l, r + 1):
        if i <= m:
            left_part.append(nums[i])
        else:
            right_part.append(nums[i])

    while li < len(left_part) and ri < len(right_part):
        if left_part[li] <= right_part[ri]:
            nums[l] = left_part[li]
            li += 1
        else:
            nums[l] = right_part[ri]
            ri += 1
        l += 1

    while li < len(left_part):
        nums[l] = left_part[li]
        l += 1
        li += 1

    while ri < len(right_part):
        nums[l] = right_part[ri]
        l += 1
        ri += 1


def main():
    nums = [1, 3, 2, 6, 7, 5]
    merge_sort(nums, 0, len(nums) - 1)
    print nums


if __name__ == '__main__':
    main()

