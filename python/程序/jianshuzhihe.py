#!/usr/bin/env python
# coding=utf-8

n=raw_input()
nums=[int(x) for x in raw_input().split()]
target=int (raw_input())
#print target
for i in xrange(len(nums)):
   # print len(nums)
    for j in xrange(i + 1, len(nums)):
        #print nums[i] + nums[j]
        temp = nums[i] + nums[j]
        #print temp == target
        if nums[i] + nums[j] == target:
            print  i+1,j+1
            break
