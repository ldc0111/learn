#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
template<typename T>
class Array{
    private:
    	int size,number;
    	T *data;
    public:
    	Array(int si) {
            size = si;
            number = 0;
            data = new T[size];
        }
    	void insert(T value){
            if(number == size) {
                cout << "array full" << endl;
                return ;
            }
            data[number++] = value;
        }
    	void showAll(){
            for (int i = 0; i < number; i++) {
                cout << data[i] << endl;
            }
        }
    	~Array(){
            delete [] data;
        }
};

int main() {
    string str1="yangzhou301";
    Array<char> arr1(str1.length());
    for(auto c:str1)
    {
        arr1.insert(c);
    }
    arr1.showAll();
    int num[]={1,9,2,6,0,8,1,7};
    Array<int>arr2(sizeof(num)/sizeof(int));
    for(auto c:num)
    {
        arr2.insert(c);
    }
	arr2.showAll();
    arr2.insert(301);
    return 0;
}
