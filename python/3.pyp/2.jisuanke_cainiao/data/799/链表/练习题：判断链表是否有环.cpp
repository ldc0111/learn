#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int val;
    struct Node *next;
} ListNode;
#define bool int
#define true 1
#define false 0
/**
 * 已经定义的 ListNode 结点
 * typedef struct Node {
 *     int val;
 *     struct Node *next;
 * } ListNode;
 * #define bool int
 * #define true 1
 * #define false 0
 */
bool isLinkedListCycle(ListNode *head) {
    if (head == NULL) return 0;
    if (head == head->next) return 1;
    ListNode *so = head,*qu = head;
    while (so != NULL && qu != NULL) {
        so = so->next;
        if (qu->next == NULL) return 0;
        else qu = qu->next->next;
        if (so == qu) return 1;
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
    if (isLinkedListCycle(head)) {
        printf("Cycle\n");
    } else {
        printf("No cycle\n");
    }
    return 0;
}