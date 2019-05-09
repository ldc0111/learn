#include <cstdio>
#include <iostream>
using namespace std;
int main() {
    int n;
    int k;
    int numbers[1000001];
    int m;
    int i,j;
    int flag = 0;

    // 反复读入数字和查找数字的数量
    while (scanf("%d %d", &n, &k) != EOF) {

        // 读入给定的数字
        for (i = 0; i < n; i++) {
            scanf("%d", &numbers[i]);
        }

        for (j = 0; j < k; j++) {
            // 读入待查找的数字，
            scanf("%d", &m);
			flag = 0;
            // 请在下面完成查找读入数字的功能
            int head = 0,tail = n - 1;
            while (head < tail){
                int mid = (head + tail) >> 1;
                //cout << numbers[mid] << m << endl;
                if(numbers[mid] == m) {
                    cout << mid + 1;
                    flag = 1;
                    if(j != k - 1) cout << " ";
                    else cout << endl;
                    break;
                } else if (numbers[mid] < m) head = mid + 1;
                else tail = mid;
            }
            if (flag == 0) {
                cout << "0";
                if(j != k - 1) cout << " ";
                else cout << endl;                
            }
        }

    }
    return 0;
}