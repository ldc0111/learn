/*************************************************************************
	> File Name: 5.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年03月28日 星期四 21时27分19秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include <functional>
using namespace std;

auto in_range = [](int b, int e) {
    return [=](int x) -> bool {
        return (x <= e) && (x >= b);
    };
};

auto OR = [](function<bool(int)> f, function<bool(int)> g) {
    return [=](int x) {
        return (f(x) || g(x));
    };
};

auto AND = [](function<bool(int)> f, function<bool(int)> g) {
    return [=](int x) {
        return (f(x) && g(x));
    };
};

bool is_prime(int x) { return true; }
bool is_odd(int x) { return true; }

auto is_digit = in_range('0', '9');
auto is_alpha = OR(in_range('a', 'z'), in_range('A', 'Z'));
auto is_valid = AND(is_prime, is_odd);

auto all_digit = [](string str) -> bool {
    for (auto x : str) {
        if (!is_digit(x)) return false;
    }
    return true;
};

auto all_alpha = [](string str) -> bool {
    for (auto x : str) {
        if (!is_alpha(x)) return false;
    }
    return true;
};

class Base {
public :
    Base() {
        next = nullptr;
    }
    virtual bool test(string &str) = 0;
    virtual void do_something() = 0;
    friend Base *getLink();
    
    static void run(string &str);
private:
    Base *next;
    static Base *head;
};

Base *Base::head = nullptr;

class A : public Base {
public :
    bool test(string &str) {
        if (str.size() == 1 && str == ".") return true;
        return false;
    }
    void do_something() {
        cout << 1 << endl;
    }
};

class B : public Base {
public :
    bool test(string &str) {
        return all_digit(str);
    }
    void do_something() {
        cout << 2 << endl;
    }
};

class C : public Base {
public :
    bool test(string &str) {
        return all_alpha(str);
    }
    void do_something() {
        cout << 3 << endl;
    }
};

class D : public Base {
public :
    bool test(string &str) {
        return true;
    }
    void do_something() {
        cout << 4 << endl;
    }
};

Base *getLink() {
    if (Base::head) return Base::head;
    Base::head = new A;
    Base::head->next = new B;
    Base::head->next->next = new C;
    Base::head->next->next->next = new D;
    return Base::head;
}

void Base::run(string &str) {
    Base *p = getLink();
    while (p && p->test(str) == false) {
        p = p->next;
    }
    if (p == nullptr) return ;
    p->do_something();
    return ;
}

int main() {
    string str;
    while (cin >> str) Base::run(str);
    return 0;
}
