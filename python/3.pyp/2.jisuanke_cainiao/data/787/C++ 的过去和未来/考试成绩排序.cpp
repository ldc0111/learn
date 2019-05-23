#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class people{
    public:
    string name;
    int fen;
    people();
    people(string na, int in) {
        name = na;
        fen = in;
    }
};

int main(){
    vector<people> arr;
    int input;
    string name;
    while (cin >> name >> input) {
        people temp(name,input);
        arr.push_back(temp);
    }
    sort(arr.begin(),arr.end(),[](people x, people y){return x.fen < y.fen;});
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i].name << " " << arr[i].fen << endl;
    }
    cout << arr.size() << endl;
    return 0;
}