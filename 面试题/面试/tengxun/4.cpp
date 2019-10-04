/*************************************************************************
	> File Name: 4.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月20日 星期五 21时18分01秒
 ************************************************************************/

#include <iostream>
using namespace std;

#define swap(a,b) {\
                      __typeof(a) _t = a;\
                                  a = b;\
                                  b = _t;\
                  }

typedef struct priority_queue{
        int *data;
        int size,cnt;

}priority_queue;

priority_queue *init(int n) {
        priority_queue *q = (priority_queue *)malloc(sizeof(priority_queue));
        q->data = (int *)malloc(sizeof(int) * (n + 1));
        q->cnt = 0;
        q->size = n;
        return q;

}

int empty(priority_queue *q) {
        return q->cnt == 0;

}
int push(priority_queue *q, int value) {
        if (q->cnt == q->size) return 0;
        q->data[++q->cnt] = value;
        int ind = q->cnt;
    while (ind > 1) {
                if (q->data[ind] <=  q->data[ind >> 1]) break;
                swap(q->data[ind],q->data[ind >> 1]);
                ind >>= 1;
            
    }
        return 1;

}


int pop(priority_queue *q) {
        if (empty(q)) return 0;
        q->data[1] = q->data[q->cnt--];
        int ind = 1;
    while ((ind << 2) < q->cnt) {
                int temp = ind;
                if (q->data[temp] < q->data[ind << 1]) temp = ind << 1;
                if (((ind << 1 | 1) < q->cnt) && q->data[temp] < q->data[(ind << 1 | 1)]) temp = ind << 1 | 1;
                if (temp == ind) break;
                swap(q->data[temp], q->data[ind]);
                ind = temp;
            
    }
        return 1;

}

int top(priority_queue *q) {
        if (empty(q)) return 0;
        return q->data[1];

}




int main() {
    int n,k,a;
    priority_queue *q;
    q = init(10005);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a;
        push(q,a);
    }
    long long t = 0;
    for (int i = 0; i < k && !empty(q); i++) {
        while(top(q) == 0 || top(q) == t) pop(q);
        cout << top(q) - t << endl;
        t += top(q);
        pop(q);
    }

    return 0;
}
