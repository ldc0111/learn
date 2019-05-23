#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int val;
    struct Node *pre;
    struct Node *next;
} ListNode;
/**
 * 已经定义的 ListNode 结点
 * typedef struct Node {
 *     int val;
 *     struct Node *pre;
 *     struct Node *next;
 * } ListNode;
 */
ListNode* reverseLinkedList(ListNode *head) {
    if (head == NULL) return 0;
    ListNode *current = head, *p = head->next, *q;
    head->pre = p;
    while (p) {
        q = p->next;
        p->pre = q;
        p->next = current;
        current = p;
        p = q;
    }
    head->next = NULL;
    return current;
}
int main() {
    int n;
    scanf("%d", &n);
    ListNode* head = (ListNode*)malloc(sizeof(ListNode));
    head->val = 0;
    head->next = NULL;
    head->pre = NULL;
    ListNode *temp = head;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        temp->next = (ListNode*)malloc(sizeof(ListNode));
        temp->next->val = x;
        temp->next->next = NULL;
        temp->next->pre = temp;
        temp = temp->next;
    }
    temp = head;
    head = head->next;
    head->pre = NULL;
    free(temp);
    head = reverseLinkedList(head);
    temp = head;
    while (head) {
        printf("%d ", head->val);
        head = head->next;
        free(temp);
        temp = head;
    }
    printf("\n");
    return 0;
}