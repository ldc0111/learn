#include <iostream>
#include <algorithm>
#include <map>
#include <queue>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    string name;
    double f;
    map<string, priority_queue<double> > mp;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> name >> f;
        mp[name].push(f);
    }
    map<string, double> mp1;
    for (auto i = mp.begin(); i != mp.end(); i++) {
        double sum = 0;
        int j = 0;
        int size = i->second.size();
        for (; j < 5 & j < size; j++) {
            sum += mp[i->first].top();
            mp[i->first].pop();
        }
        mp1[i->first] = sum / (size > 5 ? 5 : size);
    }
    vector<pair<string, double> > arr;
    
    for (auto i = mp1.begin(); i != mp1.end(); i++) {
        arr.push_back(make_pair(i->first,i->second));
        //cout << i->first << " " << i->second << endl;
    }
    sort(arr.begin(),arr.end(),[](auto x,auto y) {
        if (x.second >= y.second) {
            if(x.second == y.second) {
                return x.first < y.first;
            }
            return true;
        }
        return false;});
    cout<<setiosflags(ios::fixed)<<setprecision(2);
    for (auto i = arr.begin(); i != arr.end(); i++) {
        cout << i->first << " " << i->second << endl;
    }
    return 0;
}
