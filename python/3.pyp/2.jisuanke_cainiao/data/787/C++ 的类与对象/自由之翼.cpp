#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

class Terran{
    private:
    	int SCV,Marine,Medic;
    	int num1,num2,num3;
    	int bian,time;
    	string name;
    public:
    	Terran(string na){
            SCV = 10;
            Marine = 5;
            Medic = 4;
            bian = time = num1 = num2 = num3 = 0;
            name = na;
            
        }
    	void set_scv(int &n) {
            if (n < 10) return ;
            num1++;
            n -= 10;
            cout << "Time: " << time << "  " << name <<" SCV " << bian << " born with HP 10 " << num1 << " SCV in base " << name << endl;
            //printf("Time: %d  %s SCV %d born with HP 10 %d SCV in base %s",time, name, bian, num1,name);
            bian++;
            time++;
        }
    	void set_marine(int &n) {
            if (n < 5) return ;
            num2++;
            n -= 5;
            cout << "Time: " << time << "  " << name <<" Marine " << bian << " born with HP 5 " << num2 << " Marine in base " << name << endl;
            //printf("Time: %d  %s Marine %d born with HP 10 %d Marine in base %s",time, name, bian, num2,name);
            bian++;
            time++;
        }
    	void set_medic(int &n) {
            if (n < 4) return ;
            num3++;
            n -= 4;
            cout << "Time: " << time << "  " << name <<" Medic " << bian << " born with HP 4 " << num3 << " Medic in base " << name << endl;
            //printf("Time: %d  %s Medic %d born with HP 10 %d Medic in base %s",time, name, bian, num3,name);
        	bian++;
            time++;
        }
    	void over(){
            time--;
            bian--;
            cout << "Time: " << time << "  " << name << " base stop training troopers." << endl;
            //printf("Time: %d  %s base stop training troopers.", time, name);
        }
};


int main() {
    int n,a;
    Terran ta("Raynor");
    Terran te("Mengsk");
    cin >> n;
    a = n;
    while(a >=  4){
        ta.set_scv(a);
        ta.set_marine(a);
        ta.set_medic(a);
    }
    ta.over();
    a = n;
    while(a >=  4){
        te.set_marine(a);
        te.set_medic(a);
        te.set_scv(a);
    }
    te.over();
    return 0;
}