/*************************************************************************
	> File Name: complex.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月18日 星期五 16时20分10秒
 ************************************************************************/

#include<iostream>
using namespace std;

class Complex{
    private:
        double real;
        double imag;
    public:
        Complex(double r = 0, double i = 0) :real(r), imag(i){
            
        }
        int getR(){
            return this->real;
        }
        int getI() {
            return this->imag;
        }
    Complex operator+(Complex &c2);
    //friend Complex operator+(Complex &c1, Complex &c2);
    Complex operator-(Complex &c2);
    Complex operator*(Complex &c2);
    Complex operator/(Complex &c2);
    bool operator==(Complex &c2);
    bool operator!=(Complex &c2);
    Complex& operator=(const Complex &c2){ 
        //不允许自赋值 a = a；
        if (this != &c2){
            this->real = c2.real;
            this->imag = c2.imag;
        }
        return *this;
    }
};

Complex Complex::operator+(Complex &c2) {
    Complex ret;
    ret.real = this->real + c2.real;
    ret.imag = this->imag + c2.imag;
    return ret;
}

Complex Complex::operator-(Complex &c2) {
    Complex ret;
    ret.real = this->real - c2.real;
    ret.imag = this->imag - c2.imag;
    return ret;
}


Complex Complex::operator*(Complex &c2) {
    Complex ret;
    ret.real = this->real * c2.real - this->imag * c2.imag;
    ret.imag = this->real * c2.imag + this->imag * c2.real;
    return ret;
}

Complex Complex::operator/(Complex &c2) {
    Complex ret;
    ret.real = (this->real * c2.real + this->imag * c2.imag)/(c2.real * c2.real + c2.imag * c2.imag);
    ret.imag = (this->real * c2.imag - this->imag * c2.real)/(c2.real * c2.real + c2.imag * c2.imag);
    return ret;
}

bool Complex::operator==(Complex &c2) {
    if(this->real == c2.real && this->imag == c2.imag) {
        return 1;
    }
    return 0;
}

bool Complex::operator!=(Complex &c2) {
    if(this->real == c2.real && this->imag == c2.imag) {
        return 0;
    }
    return 1;
}
/*
Complex operator+(Complex &c1 ,Complex &c2) {
    Complex ret;
    ret.real = c1.real + c2.real;
    ret.imag = c1.imag + c2.imag;
    return ret;
}*/

/*
int main() {
    Complex c1 = {1,2};
    Complex c2 = {2,3};
    Complex c3;
    Complex c4;
    c3 = c1 + c2;
    cout << c3.getR() << " " << c3.getI() << "i" << endl;
    c3 = c1 - c2;
    cout << c3.getR() << " " << c3.getI() << "i" << endl;
    c3 = c1 * c2;
    cout << c3.getR() << " " << c3.getI() << "i" << endl;
    c3 = c2 / c1;
    cout << c3.getR() << " " << c3.getI() << "i" << endl;
    return 0;
}
*/

int main() {
    Complex c1 = {1,2};
    Complex c2 = {2,3};
    Complex c3;
    c3 = c1 + c2;
    cout << c3.getR() << " " << c3.getI() << "i" << endl;

    return 0;
}
