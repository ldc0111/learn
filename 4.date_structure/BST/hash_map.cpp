/*************************************************************************
	> File Name: hash_map.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年04月18日 星期四 16时50分22秒
 ************************************************************************/

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;
int main(){
    unordered_map<int, string> mymap;
    mymap[9527]="唐伯虎点秋香";
    mymap[1000000]="百万富翁的生活";
    mymap[10000]="白领的工资底线";
    mymap.insert(pair<int ,string>(1004,"lidecao"));
    cout << "bucket  " << mymap.bucket_count() << endl;
    if(mymap.find(1004) != mymap.end()){
        cout << " begin: " << (mymap.begin()->first) << endl;
        cout << "find : " << endl;
    }
}
