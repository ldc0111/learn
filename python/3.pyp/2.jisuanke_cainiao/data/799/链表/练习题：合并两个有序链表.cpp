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
ListNode* mergeTwoSortedLinkList(ListNode *head1, ListNode *head2) {
    ListNode ret, *p;
    p = &ret;
    while (head1 != NULL && head2 != NULL) {
        if (head1->val <= head2->val) {
            p->next = head1;
            head1 = head1->next;
        } else {
            p->next = head2;
            head2 = head2->next;
        }
        p = p->next;
    }
    if (head1 != NULL) {
        p->next = head1;
    }
    if (head2 != NULL) {
        p->next = head2;
    }
    return ret.next;
}
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
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
    ListNode *head2 = (ListNode*)malloc(sizeof(ListNode));
    head2->val = 0;
    head2->next = NULL;
    temp = head2;
    for (int i = 0; i < m; ++i) {
        int x;
        scanf("%d", &x);
        temp->next = (ListNode*)malloc(sizeof(ListNode));
        temp->next->val = x;
        temp->next->next = NULL;
        temp = temp->next;
    }
    temp = head2;
    head2 = head2->next;
    free(temp);
    head = mergeTwoSortedLinkList(head, head2);
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