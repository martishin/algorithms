#!/usr/bin/env python


import heapq


def heap_sort(nums):
    heap = []

    for v in nums:
        heapq.heappush(heap, v)

    for i in range(len(nums)):
        nums[i] = heapq.heappop(heap)


def main():
    nums = [1, 3, 2, 6, 5, 7]
    heap_sort(nums)
    print nums


if __name__ == '__main__':
    main()
