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
ListNode* reverseLinkedList(ListNode *head) {
    if (head == NULL) return NULL;
    ListNode *current = head;
    ListNode *p,*q;
    p = current->next;
    
    while (p != NULL) {
    	q = p->next;//缓存下一个节点
        p->next = current;//改变指向下一个节点
        current = p;//后移
        p = q;//后移
        
    }
    head->next = NULL;  
    return current;
}
int main() {
    int p[4020000] = {0};
    memset(p, 0, sizeof p);
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
    temp = head;
    head = head->next;
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