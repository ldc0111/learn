#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> arr;
    int input;
    while(cin >> input){
        auto iter = find(arr.begin(), arr.end(), input);
        if(iter == arr.end()){
            arr.push_back(input);
        }
    }
    sort(arr.begin(), arr.end(),greater<int>());
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << endl;
    }
    cout << arr.size();
}