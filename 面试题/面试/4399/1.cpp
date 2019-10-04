/*************************************************************************
	> File Name: 1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月25日 星期三 19时23分25秒
 ************************************************************************/

#include<iostream>
using namespace std;
//16,17,33,38,42,56,72,73
int bin_find(int arr[],int arr_size,int num) {
    int l = 0,r = arr_size - 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (arr[mid] == num) return mid;
        else if (arr[mid] > num) r = mid - 1;
        else l = mid + 1;
    }
    return -1;
}


int main() {
    int arr[8] = {16,17,33,38,42,56,72,73};

    cout << bin_find(arr,8,42);
    cout << bin_find(arr,8,16);
    cout << bin_find(arr,8,17);
    cout << bin_find(arr,8,33);
    cout << bin_find(arr,8,38);
    cout << bin_find(arr,8,56);
    cout << bin_find(arr,8,7);
    


    return 0;
}
