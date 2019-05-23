/*************************************************************************
	> File Name: 4.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年03月07日 星期四 18时24分05秒
 ************************************************************************/

#include<iostream>
#include <string.h>
using namespace std;

class pre{
    public:
    int i;
    int get() {
        //return this->i;
        return this->a;
    }
    protected:
    int j;
    private:
    int a,b;
};

class a : public pre{
    public:
    int geti(){
        return this->i;
    }
    int getj(){
        return this->j;
    }
    int getk(){
        return this->k;
    }
   /* 
    int geta(){
        return this->a;
    }
    int getb(){
        return this->b;
    }*/
    protected:

    private:
    int k;
};


class b : protected pre{
    public:
    int geti(){
        return this->i;
    }
    int getj(){
        return this->j;
    }
    int getk(){
        return this->k;
    }
    int ge(){
        return get();
    }
    /*
    int geta(){
        return this->a;
    }
    int getb(){
        return this->b;
    }*/
    protected:
    int k;

    private:
};

class c : private pre{
    public:
    int geti(){
        return this->i;
    }
    int getj(){
        return this->j;
    }
    int getk(){
        return this->k;
    }
    /*
    int geta(){
        return this->a;
    }
    int getb(){
        return this->b;
    }*/
    protected:

    private:
    int k;
};


class d : protected b{
    public:
    int geti(){
        return this->i;
    }
    int getj(){
        return this->j;
    }
    int getk(){
        return this->k;
    }
    /*
    int geta(){
        return this->a;
    }
    int getb(){
        return this->b;
    }*/
    protected:

    private:
};

int main() {
    cout << sizeof(pre) << endl;
    cout << sizeof(a) << endl;
    a test1;
    b test2;
    //c test3;
    cout << test1.get() << endl;
    cout << test2.ge() << endl;
    return 0;
    return 0;
}
