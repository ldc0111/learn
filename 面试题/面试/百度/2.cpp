/*************************************************************************
*  > File Name: 2.cpp
*      > Author: 
*          > Mail: 
*              > Created Time: 2019年09月24日 星期二 19时57分30秒
*               ************************************************************************/

 #include<iostream>
 #include <map>
 using namespace std;



 int main() {
     long long t,n;
     cin >> t;
     while (t--) {
         cin >> n;
         map<int, int> mp;
         long long temp = 0,flag = 1,sum = 0,ans = 0;
         for (int i = 0; i < n; i++) {
             cin >> temp;
             sum += temp;
             mp[temp] += 1;
             ans += i;
             if (mp[temp] >= 3) flag = 0;

         }
         if (sum == 0 || flag == 0 || sum < ans) {
             cout << "woman" << endl;
             continue;

         }
         int an =0;
         for (auto a = mp.begin(); a != mp.end();a++) {
             if (a->second >= 2) an++;

         }
         if (an > 1) {
             cout << "woman" << endl;
             continue;

         }
         if ((sum - ans) % 2 == 0) {
             cout << "woman" << endl;

         } else {
             cout << "man" << endl;

         }

     }


     return 0;

 }

