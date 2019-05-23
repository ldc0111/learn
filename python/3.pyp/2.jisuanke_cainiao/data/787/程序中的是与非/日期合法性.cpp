#include <iostream>
using std::cin;
using std::cout;
using std::endl;
int leap_year(int year){
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int main(){
    int year,mon,day;
    int a[13] = {0,31,28,31,30,
                31,30,31,31,
                30,31,30,31};
    cin >> year >> mon >> day;
    mon = -mon, day = -day;
    if(mon <= 0 || mon > 12 || day <= 0) {
        cout << "NO";
        return 0;
    }
    if(mon == 2) {
        if (day <= leap_year(year) + a[2]){
            cout << "YES";
        } else {
            cout << "NO";
        }
    } else {
        if (day <= a[mon]) {
            cout << "YES";
        } else {
            cout << "NO";
        }
    }
    return 0;
}