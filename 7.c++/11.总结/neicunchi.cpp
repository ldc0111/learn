/*************************************************************************
	> File Name: neicunchi.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年03月24日 星期日 20时29分26秒
 ************************************************************************/

#include<iostream>
using namespace std;

class Node{
    public:
    Node () : lchild(nullptr), rchild(nullptr) {};
    private:
    Node *lchild, *rchild;
    int val;
};

template<typename T>
class Pos{
    public :
    class NEI : public T{
        public:
        NEI(): used(false), next(nullptr) {}
        bool used;
        NEI * next;
    };
    //构造内池子
    Pos(int CAP) :size(CAP){
        buffer = new NEI[size];
        initPool();
    }
    T *get() {
       if (unused == nullptr) return nullptr;
        NEI *p = unused;
        unused = unused->next;
        p->used = true;
        return p;
    }    
    void clear(T *o){
        //合法性判断
        //T不是你写的虚函数NEI *obj = dynamic_cast<NEI *> (o);
        NEI *obj = reinterpret_cast<NEI *> (o);
        if (obj->used == false) return ;
        obj->used = true;
        obj->next = unused;
        unused = obj;
    }
    ~Pos() {
        delete [] buffer;
    }
    private:
    Pos(){}
    void initPool() {
        unused = &buffer[0];
        for (int i = 0; i < size; i++) {
            if (i != size - 1) buffer[i].next = buffer + i + 1;
        }
        return ;
    }
    NEI *buffer;//内存指针
    NEI *unused;//指向没有使用的内存
    size_t size;
};

int main() {
    Pos<Node> p(10);
    Node *p1 = p.get(), *p2 = p.get();
    cout << p1 << " " << p2 << endl;
    p.clear(p1);
    p.clear(p2);
    p1 = p.get();
    cout << p1 << endl;
    return 0;
}
