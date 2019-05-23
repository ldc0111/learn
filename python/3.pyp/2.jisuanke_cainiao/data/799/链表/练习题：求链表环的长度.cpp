#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int val;
    struct Node *next;
} ListNode;
/**
 * 已经定义的 ListNode 结点
 * typedef struct Node {
 *     int val;
 *     struct Node *next;
 * } ListNode;
 */
int linkedListCycleLength(ListNode *head) {
    if (head == NULL) return 0;
    if (head == head->next) return 1;
    int flag = 0,len = 0;
    ListNode *so = head, *qu = head;
    while (so != NULL && qu != NULL && flag < 2) {
        so = so->next;
        if (qu->next == NULL) return 0;
        else qu = qu->next->next;
        if (so == qu) {
            flag++;
        }
        if(flag == 1) len++;
        else if (flag == 2) return len;
    }
    return 0;
}
int main() {
    int n;
    scanf("%d", &n);
    ListNode *head = (ListNode*)malloc(sizeof(ListNode));
    head->val = 0;
    head->next = NULL;
    ListNode *temp = head;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        temp->next = (ListNode*)malloc(sizeof(ListNode));
        temp->next->val = x;
        temp->next->next = NULL;
        temp = temp->next;
    }
    int d;
    scanf("%d", &d);
    ListNode *Nth = head;
    while (d--) {
        Nth = Nth->next;
    }
    temp->next = Nth;
    temp = head;
    head = head->next;
    free(temp);
    printf("%d\n", linkedListCycleLength(head));
    return 0;
}