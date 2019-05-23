/*************************************************************************
	> File Name: 1.quick_sort_pthread.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年04月20日 星期六 21时04分52秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define INTERVAL 100
#define swap(a, b) { \
    __typeof(a) temp = a; a = b; b = temp; \
}

typedef struct Data {
    int *num, l, r;
} Data;

typedef struct Queue {
    Data *data;
    sem_t *empty, *full;
    int head, tail;
    int push_ctrl;
} Queue;

Queue *init_queue(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (Data *)malloc(sizeof(Data) * n);
    q->empty = (sem_t *)malloc(sizeof(sem_t));
    q->full = (sem_t *)malloc(sizeof(sem_t));
    sem_init(q->empty, 0, n);//鍒ゆ柇浠诲姟闃熷垪鏄惁杩樺彲浠ユ斁鍏?
    sem_init(q->full, 0, 0);//鍒ゆ柇浠诲姟闃熷垪涓湁鍑犱釜浠诲姟
    q->head = 0, q->tail = 0;
    q->push_ctrl = 0;
    return q;
}

void push_queue(Queue *q, Data data) {
    sem_wait(q->empty);//杩涜鍑忎竴鎿嶄綔锛屽鏋滃綋鍓嶄俊鍙烽噺涓?鍊硷紝灏遍樆濉炵洿鍒颁俊鍙烽噺鍙互鍑忎竴
    while (__sync_lock_test_and_set(&(q->push_ctrl), 1));//鍘熷瓙鎿嶄綔
    memcpy(q->data + q->tail, &data, sizeof(Data));
    q->tail += 1;
    q->push_ctrl = 0;
    sem_post(q->full);
    return ;
}

Data *pop_queue(Queue *q) {
    sem_wait(q->full);
    int ind = __sync_fetch_and_add(&(q->head), 1);
    sem_post(q->empty);
    return q->data + ind;
}

void clear_queue(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q->empty);
    free(q->full);
    free(q);
    return ;
}

int thread_stop = 0;

void *thread_check(void *D) {
    Data *data = (Data *)(D);
    int flag = 1;
    while (flag) {
        flag = 0;
        for (int i = 1; i < data->r; i++) {
            if (data->num[i] >= data->num[i - 1]) continue;
            flag = 1;
            break;
        }
    }
    return NULL;
}

void quick_sort(int *num, int l, int r) {
    if (r < l) return ;
    int x = l, y = r, z = num[l + ((r - l) >> 1)];
    do {
        while (num[x] < z) ++x;
        while (num[y] > z) --y;
        if (x <= y) {
            swap(num[x], num[y]);
            ++x, --y;
        }
    } while (x <= y);
    quick_sort(num, l, y);
    quick_sort(num, x, r);
    return ;
}

void *thread_worker(void *D) {
    Queue *q = (Queue *)(D);
    while (1) {
        Data *data = pop_queue(q);
        if (thread_stop) break;
        int *num = data->num, l = data->l, r = data->r;
        if (r - l <= INTERVAL) {
            quick_sort(num, l, r);//小于这个值就在一个线程内排序
        } else {
            int x = l,y = r, z = num[l + ((r - l) >> 1)];
            do {//多线程排序
                while (num[x] < z) ++x;
                while (num[y] > z) --y;
                if (x <= y) {
                    swap(num[x], num[y]);
                    ++x, --y;
                }
            } while (x <= y);
            Data data;
            data.num = num; data.l = l; data.r = y;
            push_queue(q, data);
            data.num = num; data.l = x; data.r = r;
            push_queue(q, data);
        }
    }
    return NULL;
}
//用几个线程，头尾等等
void quick_sort_with_thread(int *num, int n, int thread_num) {
    Queue *q = init_queue(2 * n + 1);
    Data data;
    data.num = num; data.l = 0; data.r = n - 1;
    push_queue(q, data);
    pthread_t thread_id[thread_num];
    for (int i = 0; i < thread_num; i++) {
        pthread_create(thread_id + i, NULL, thread_worker, q);
    }
    pthread_t pcheck;
    Data thread_data = {num, 0, n - 1};
    pthread_create(&pcheck, NULL, thread_check, &thread_data);
    pthread_join(pcheck, NULL);
    thread_stop = 1;
    for (int i = 0; i < thread_num; i++) {
        sem_post(q->full);
    }
    for (int i = 0; i < thread_num; i++) {
        pthread_join(thread_id[i], NULL);
    }
    clear_queue(q);
    return ;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return 0;
    srand(time(0));
    int *num, thread_num = atoi(argv[1]);
    #define MAX 100000
    num = (int *)malloc(sizeof(int) * MAX);
    for (int i = 0; i < MAX; i++) {
        num[i] = rand() % 1000000 + 1;
    }    
    quick_sort_with_thread(num, MAX, thread_num);
    for (int i = 0; i < MAX; i++) {
        if ((i + 1) % 10 == 0) printf("\n");
        printf("%d ", num[i]);
    }
    return 0;
}
