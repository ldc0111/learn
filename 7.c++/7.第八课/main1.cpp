/*************************************************************************
	> File Name: main1.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月16日 星期三 09时53分20秒
 ************************************************************************/

#include<iostream>
#include <string>
#include <cstdio>
using namespace std;

class CompannyA_Boss{
    public:
    int battle() {
        int ret = 10;
        cout << "CompannyA_Boss :: battle = " << ret << endl;
        return ret;
    }
};

class CompannyB_Boss{
    public:
    virtual int fight() {
        int ret = 8;
        cout << "CompannyB_Boss :: battle = " << ret << endl;
        return ret;
    }
};

class CompannyB_NewBoss : public CompannyB_Boss{
    public:
    int fight() {
        int ret = this->CompannyB_Boss::fight() * 2;
        cout << "CompannyB_Boss :: battle = " << ret << endl;
        return ret;
    }
};
void vs(CompannyA_Boss *c1, CompannyB_Boss *c2) {
    int a = c1->battle();
    int b = c2->fight();
    if(a > b) {
        cout << "CompannyA A is winner" << endl;
    } else {
        cout << "CompannyB B is winner" << endl;
    }
    return ;
}





int main() {
    CompannyA_Boss c1;
    CompannyB_Boss c2;
    cout << "long long ago" << endl;
    vs(&c1,&c2);
    cout << "now" << endl;
    CompannyB_NewBoss c3;//ｎｅｗ　ｂｏｓｓ
    vs(&c1,&c3);
    return 0;
}
