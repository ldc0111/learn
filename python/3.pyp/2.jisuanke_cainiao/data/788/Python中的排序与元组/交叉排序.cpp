nums =[int(x) for x in raw_input().split()]
nums1 = []
nums2 = []

for i in xrange(len(nums)):
    ind = i + 1
    if ind % 3 != 0 and ind %2 == 0:
        nums1.append(nums[i])
    elif ind % 3 == 0:
        nums2.append(nums[i])
nums1.sort()
nums2.sort(reverse=True)
for i in xrange(len(nums)):
    ind = i + 1
    if ind % 3 != 0 and ind % 2 == 0:
        nums[i] = nums1.pop(0)
    elif ind %3 == 0:
        nums[i] = nums2.pop(0)
print ' '.join(str(x) for x in nums)