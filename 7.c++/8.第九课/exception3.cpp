/*************************************************************************
	> File Name: exception3.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月18日 星期五 15时02分49秒
 ************************************************************************/

#include<iostream>
using namespace std;



int main() {
    try {
        try {
            throw 'a';
        } catch (int i) {
            cout << "catch(int i)" << i << endl;
        } catch(...){
            cout << "catch(...)" << endl;
            throw;
        }
    } catch(char c) {
        cout << "information is " << c << endl;
    }catch (...) {
        cout << "other exception " << endl;
    }
    cout << "done" << endl;
    return 0;
}
