/*************************************************************************
	> File Name: template.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月16日 星期三 16时45分50秒
 ************************************************************************/

#include<iostream>
using namespace std;
template <typename T1, typename T2,typename T3>
T1 add(T2 a, T3 b) {
    return static_cast<T1>(a + b);
}

//多个类型参数时，返回值类型无法自动推导
//２可以从左到右给出实参类型
int main(){
    int r = add<int>(0.1, 0.6);//ｄｏｕｂｌｅ
    int r2 = add<int, float> (0.3,0.5);// T1 int t2 float, T3 double
    int r3 = add<int, float, float>(0.3,0.8);
    cout << r << endl;
    cout << r2 << endl;
    cout << r3 << endl;
    return 0;
}
