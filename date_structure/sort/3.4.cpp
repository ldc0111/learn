/*************************************************************************
	> File Name: 3.4.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年11月07日 星期三 20时33分28秒
 ************************************************************************/

#include<iostream>
using namespace std;
int binary_search(int *nums,int size,int value){//数字在这个序列中排第几位
    int head = 0,tail = size,mid = 0;
    while(head < tail){
        mid = (head + tail) >> 1;
        if(nums[mid] > value) tail = mid;
        else head = mid + 1;
    }
    return head;
}

//找到两个有序合并后，第ｋ大的元素
int binary_search2(int* nums1, int nums1Size, int* nums2, int nums2Size,int k){ 
    int head = 0,tail = nums1Size - 1,mid = 0;
    while(head <= tail){
        mid = (head + tail) >> 1;
        int temp = mid + 1 + binary_search(nums2,nums2Size,nums1[mid]);
        printf("mid %d temp %d\n",mid,temp);
        if(temp == k){
            return nums1[mid];
        }
        if(temp > k) tail = mid - 1;
        else  head = mid + 1;
    }
    
    printf("k = %d\n",k);
    head = 0, tail = nums2Size - 1,mid = 0;
    while(head <= tail){
        mid = (head + tail) >> 1;
        int temp = mid + 1 + binary_search(nums1,nums1Size,nums2[mid]);
        if(temp == k){
            return nums2[mid];
        }
        if(temp  > k) tail = mid - 1;
        else  head =mid + 1;
    }
    printf("head %d\n",head);
    return nums2[head];
}
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int pos = nums1Size + nums2Size;//
    double ans = (double)binary_search2(nums1,nums1Size,nums2,nums2Size,(pos + 1)/2);
    printf("ans = %lf\n",ans);
    if(pos % 2 == 0){
        ans += binary_search2(nums1, nums1Size, nums2, nums2Size,(pos + 1)/2 + 1);
        printf("ans = %lf\n",ans);
        ans /= 2.0;
    }
    return ans;
}

int main(){
    int a[] = {1};
    int b[] = {1};
    printf("%lf\n",findMedianSortedArrays(a,1,b,1));

    return 0;
}
