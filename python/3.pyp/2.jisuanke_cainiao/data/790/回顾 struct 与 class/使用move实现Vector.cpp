#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
class Element {
private:
    int number;
public:
	Element() :number(0) {
	    cout << "ctor" << endl;
	}
  	Element(int num):number(num) {
  		cout << "ctor" << endl;
  	}
  	Element(const Element& e):number(e.number) {
  		cout << "copy ctor" << endl;
  	}
  	Element(Element&& e):number(e.number) {
  		cout << "right value ctor" << endl;
  	}
  	~Element() {
  		cout << "dtor" << endl;
  	}
  	void operator=(const Element& item) {
  		number = item.number;
  	}
  	bool operator==(const Element& item) {
  		return (number == item.number);
  	}
  	void operator()() {
  		cout << number ;
  	}
  	int GetNumber() {
  		return number;
  	}
};
template<typename T>
class Vector {
private:
  	T* items;
  	int count;
public:
  	Vector() :count{ 0 }, items{nullptr} {

  	}
  	Vector(const Vector& vector) :count{vector.count} {
  		items = static_cast<T*>(malloc(sizeof(T) * count));
  		memcpy(items, vector.items, sizeof(T) * count);
  	}
  	Vector(Vector&& vector) :count{ vector.count }, items{ vector.items } {
  		vector.items = nullptr;
        vector.count = 0;
  	}
  	~Vector() {
  		if (this->items != nullptr) {
            for (int i = 0; i < this->count; i++) {
                this->items[i].~T();
            }
            free(this->items);
        }
  	}
    T& operator[](int index){
    	if (index<0||index>=count) {
    		cout<<"invalid index"<<endl;
    		return items[0];
    	}
    	return items[index];
    }
    int returnCount(){
    	return count;
    }
  	void Clear() {
  		//TODO
        for (int i = 0; i < this->count; i++) {
            this->items[i].~T();
        }
        free(this->items);
        this->items = nullptr;
        this->count = 0;
  	}

  	void Add(const T& item) {
  		//TODO
        int new_count = count + 1;
        T *p = static_cast<T*>(malloc(sizeof(T) * (new_count)));
        for (int i = 0; i < count; i++) {
            new(p + i) T(std::move(this->items[i]));
        }
        new(p + count) T(item);
        Clear();
        this->items = p;
        this->count = new_count;
        return ;
  	}
  	bool Insert(const T& item,int index) {
  		if (index < 0 || index > this->count) return false;
        int new_count = count + 1;
        T *p = static_cast<T*>(malloc(sizeof(T) * (new_count)));
        for (int i = count; i > index; i--) {
            new(p + i) T(std::move(this->items[i - 1]));
        }
        new(p + index) T(item);
         for (int i = 0; i < index; i++) {
            new(p + i) T(std::move(this->items[i]));
        }
        Clear();
        this->items = p;
        this->count = new_count;       
        return 1;
  	}
  	bool Remove(int index) {
  		if (index < 0 || index >= this->count) return false;
        int new_count = count - 1;
        T *p = static_cast<T*>(malloc(sizeof(T) * (new_count)));
        for (int i = 0; i < new_count; i++) {
            //printf("%d  %d  %d\n", index,i, (i + (i >= index)));
            new(p + i) T(std::move(this->items[i + (i >= index)]));
        }
        Clear();
        this->items = p;
        this->count = new_count;
        return 1;
  	}
  	int Contains(const T& item) {
  		for (int i = 0; i < this->count ; i++) {
            if (this->items[i] == item) return i;
        }
        return -1;
  	}
};
template<typename T>
void PrintVector(Vector<T>& v){
	  int count=v.returnCount();
	  for (int i = 0; i < count; i++)
	  {
		  v[i]();
		  cout << " ";
	  }
	  cout << endl;
}
int main() {
  	Vector<Element>v;
  	for (int i = 0; i < 4; i++) {
  		Element e(i);
  		v.Add(e);
  	}
  	PrintVector(v);
  	Element e2(4);
  	if (!v.Insert(e2, 10))
  	{
  		v.Insert(e2, 2);
  	}
  	PrintVector(v);
  	if (!v.Remove(10))
  	{
  		v.Remove(2);
  	}
  	PrintVector(v);
  	Element e3(1), e4(10);
  	cout << v.Contains(e3) << endl;
  	cout << v.Contains(e4) << endl;
  	Vector<Element>v2(v);
  	Vector<Element>v3(move(v2));
  	PrintVector(v3);
  	v2.Add(e3);
  	PrintVector(v2);
  	return 0;
}
