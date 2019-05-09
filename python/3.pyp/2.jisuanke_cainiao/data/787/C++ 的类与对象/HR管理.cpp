#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
class People {
    private:
    	int number;//编号
    	string name;//姓名
    	string gender;//性别
    	string ID;//身份证号
    	double salary;//工资
    public:
   		People(int nu,string na, string ge, string I,double sa) {
            number = nu;
            name = na;
            gender = ge;
            ID = I;
            salary = sa;
            cout << "calling the constructor" << endl;
    	}
    	People(const People &p){
            number = p.number + 1;
            name = p.name;
            gender = p.gender;
            ID = p.ID;
            salary = p.salary;
            cout << "calling the copy constructor" << endl;
        }
     	~People(){
        	cout << "calling the destructor" << endl;
     	}
    	void set_name(string na){
            name = na;
        }
    	void set_salary(double sa){
            salary = sa;
        }
    	void set_number(int nu){
            number = nu;
        }
    	void set_gender(string ge){
            gender = ge;
        }
    	void set_ID(string I){
            ID = I;
        }
    	void show(){
            cout << number << " " << name << " " << gender << " " << ID << " " << salary << endl;
        }
    	
};

int main() {
    People p1(01, "qratosone", "Male", "2010201326", 4800.0);
    People p2(p1);
    p2.set_name("He");
    p2.set_salary(301.301);
    p1.show();
    p2.show();
    string new_name;
    cin>>new_name;
    People p3(p2);
    p3.set_name(new_name);
    p3.show();
    return 0;
}