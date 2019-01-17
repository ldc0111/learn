/*************************************************************************
	> File Name: virtual_func.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月16日 星期三 14时22分10秒
 ************************************************************************/

#include<iostream>
using namespace std;

class shap{
    public:
    virtual double area() = 0;
    //有纯虚函数的类就叫做纯虚函数
    //virtual void print() = 0;
};


class Rect: public shap{
    private:
    double h,w;
    public:
        Rect(double v1, double v2) {
            h = v1;
            w = v2;
        }
        double area() {
            return h * w;
        }
};

class Circle : public shap{
    private:
        double r;
    public:
        Circle(double v1) {
            r = v1;
        }
        double area() {
            return 3,14  * r * r;
        }
};


int main() {
    Rect r(3.2, 4.5);
    Circle c(0.4);
    cout << r.area() << endl;
    cout << c.area() << endl;
    return 0;
}
