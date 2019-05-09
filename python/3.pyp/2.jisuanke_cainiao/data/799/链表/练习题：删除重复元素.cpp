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
ListNode* twoWayLinkListUnique(ListNode *head) {
    if (head == NULL) return ;
    ListNode *p = head, *q, *qx,*qy;
    for (;p != NULL;p = p->next) {
        q = p->next;
        qx = p;
        while (q != NULL) {
            if (p->val == q->val) {
                qy = q->next;
                if (qy != NULL) qy->pre = qx;
                qx->next = qy;
                free(q);
                q = qy;
            } else {
                q = q->next;
                qx = qx->next;
            }
        }
    }
    return head;
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
        temp->next->pre = NULL;
        temp = temp->next;
    }
    temp = head;
    head = head->next;
    head->pre = NULL;
    free(temp);
    head = twoWayLinkListUnique(head);
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