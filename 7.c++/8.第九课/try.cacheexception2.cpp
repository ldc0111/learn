/*************************************************************************
	> File Name: exception2.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月18日 星期五 14时42分17秒
 ************************************************************************/

#include<iostream>
using namespace std;

/*


int main() {
    //严格匹配
    try{
        throw 1;
    } catch(char c) {
        cout << "catch(char c)" << endl;
    } catch(short s) {
        cout << "catch (short s)" << endl;
    } catch(double d) {

    } catch (double d) {
        cout << "catch(double d)" << endl;
    } catch (int i) {
        cout << "catch(int i)" << endl;
    } catch (...) {
        cout << "catch(...)" << endl;
    }

    cout << "finshed" << endl;
    return 0;
}*/

class A
{
public:
virtual void func(int val = 1)
{ std::cout<<"A->"<<val <<std::endl;}
virtual void test()
{ func();}
};
class B : public A
{
public:void func(int val=0)
{std::cout<<"B->"<<val <<std::endl;}
};
int main(int argc ,char* argv[])
{
B*p = new B;
p->test();
return 0;
}
